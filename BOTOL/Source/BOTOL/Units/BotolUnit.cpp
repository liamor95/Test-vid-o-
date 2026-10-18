#include "Units/BotolUnit.h"

#include "AbstractNavData.h"
#include "AIController.h"
#include "AITypes.h"
#include "BOTOL.h"
#include "NavigationSystem.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Data/BotolUnitData.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "UObject/ConstructorHelpers.h"

namespace BotolUnitDefaults
{
	constexpr float CapsuleRadius = 40.f;
	constexpr float CapsuleHalfHeight = 90.f;
	constexpr float MoveSpeed = 300.f;
	constexpr float MaxHealth = 100.f;
	constexpr float MoveAcceptanceRadius = 20.f;
	// Paramètre de couleur du matériau moteur BasicShapeMaterial.
	const FName ColorParameter(TEXT("Color"));

	/** Vrai si le niveau contient un acteur NavMesh (pas seulement les données de navigation abstraites par défaut). */
	static bool HasNavMesh(UWorld* World)
	{
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
		if (!NavSystem)
		{
			return false;
		}
		const ANavigationData* NavData = NavSystem->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
		return NavData && !NavData->IsA<AAbstractNavData>();
	}

	/**
	 * Vrai si l'unité se tient réellement sur le NavMesh. Faux si le maillage n'a pas de tuiles
	 * (volume de navigation supprimé, génération pas finie) ou si l'unité est en dehors.
	 */
	static bool IsUnitOnNavMesh(const ACharacter& Unit)
	{
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(Unit.GetWorld());
		if (!NavSystem)
		{
			return false;
		}
		FNavLocation OnNavMesh;
		return NavSystem->ProjectPointToNavigation(Unit.GetNavAgentLocation(), OnNavMesh, INVALID_NAVEXTENT, &Unit.GetNavAgentPropertiesRef());
	}
}

ABotolUnit::ABotolUnit()
{
	// Le déplacement est géré par son composant ; l'acteur lui-même n'a pas besoin de Tick.
	PrimaryActorTick.bCanEverTick = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AAIController::StaticClass();

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->InitCapsuleSize(BotolUnitDefaults::CapsuleRadius, BotolUnitDefaults::CapsuleHalfHeight);
	// La capsule répond aux traces « Visibility » : c'est elle que le doigt touche pour sélectionner.
	Capsule->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->bOrientRotationToMovement = true;
	Movement->RotationRate = FRotator(0.f, 540.f, 0.f);
	Movement->MaxWalkSpeed = BotolUnitDefaults::MoveSpeed;
	// NavWalking : l'unité glisse sur le NavMesh au lieu de tester le sol à chaque image. Bien plus léger
	// avec beaucoup d'unités. Sans NavMesh, le moteur repasse automatiquement en marche classique.
	Movement->DefaultLandMovementMode = MOVE_NavWalking;

	USkeletalMeshComponent* MeshComponent = GetMesh();
	MeshComponent->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -BotolUnitDefaults::CapsuleHalfHeight), FRotator(0.f, -90.f, 0.f));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetGenerateOverlapEvents(false);
	// L'animation n'est calculée que si l'unité est à l'écran, et moins souvent quand elle est loin.
	MeshComponent->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	MeshComponent->bEnableUpdateRateOptimizations = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BasicMaterial(TEXT("/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial"));

	PlaceholderBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaceholderBody"));
	PlaceholderBody->SetupAttachment(Capsule);
	PlaceholderBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PlaceholderBody->SetGenerateOverlapEvents(false);
	// Le cylindre moteur mesure 100 x 100 cm, centré : on l'ajuste à la capsule.
	PlaceholderBody->SetRelativeScale3D(FVector(0.8f, 0.8f, 1.8f));

	SelectionRing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectionRing"));
	SelectionRing->SetupAttachment(Capsule);
	SelectionRing->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SelectionRing->SetGenerateOverlapEvents(false);
	SelectionRing->SetCastShadow(false);
	SelectionRing->SetRelativeLocation(FVector(0.f, 0.f, -BotolUnitDefaults::CapsuleHalfHeight + 2.f));
	SelectionRing->SetRelativeScale3D(FVector(1.3f, 1.3f, 0.02f));
	SelectionRing->SetVisibility(false);

	if (CylinderMesh.Succeeded())
	{
		PlaceholderBody->SetStaticMesh(CylinderMesh.Object);
		SelectionRing->SetStaticMesh(CylinderMesh.Object);
	}
	if (BasicMaterial.Succeeded())
	{
		PlaceholderBody->SetMaterial(0, BasicMaterial.Object);
		SelectionRing->SetMaterial(0, BasicMaterial.Object);
	}
}

void ABotolUnit::BeginPlay()
{
	Super::BeginPlay();
	ApplyUnitData();
}

void ABotolUnit::InitUnit(UBotolUnitData* InUnitData, int32 InTeamId, FLinearColor InTeamColor)
{
	UnitData = InUnitData;
	TeamId = InTeamId;
	TeamColor = InTeamColor;
	ApplyUnitData();
}

void ABotolUnit::ApplyUnitData()
{
	GetCharacterMovement()->MaxWalkSpeed = UnitData ? UnitData->MoveSpeed : BotolUnitDefaults::MoveSpeed;
	CurrentHealth = UnitData ? UnitData->MaxHealth : BotolUnitDefaults::MaxHealth;

	const bool bHasRealMesh = UnitData && UnitData->SkeletalMesh;
	if (bHasRealMesh)
	{
		GetMesh()->SetSkeletalMeshAsset(UnitData->SkeletalMesh);
		if (UnitData->AnimClass)
		{
			GetMesh()->SetAnimInstanceClass(UnitData->AnimClass);
		}
	}
	PlaceholderBody->SetVisibility(!bHasRealMesh);

	ApplyColors();
}

void ABotolUnit::ApplyColors()
{
	if (!BodyMaterial)
	{
		BodyMaterial = PlaceholderBody->CreateDynamicMaterialInstance(0);
	}
	if (!RingMaterial)
	{
		RingMaterial = SelectionRing->CreateDynamicMaterialInstance(0);
	}
	if (BodyMaterial)
	{
		BodyMaterial->SetVectorParameterValue(BotolUnitDefaults::ColorParameter, TeamColor);
	}
	if (RingMaterial)
	{
		RingMaterial->SetVectorParameterValue(BotolUnitDefaults::ColorParameter, FLinearColor(1.f, 0.85f, 0.2f));
	}
}

UBotolUnitData* ABotolUnit::GetUnitData() const
{
	return UnitData.Get();
}

void ABotolUnit::SetSelected(bool bInSelected)
{
	bSelected = bInSelected;
	SelectionRing->SetVisibility(bSelected);
}

void ABotolUnit::CommandMoveTo(const FVector& Destination)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController)
	{
		return;
	}

	// Avec un NavMesh, une destination hors du maillage est refusée, au lieu d'envoyer l'unité en ligne droite
	// à travers les obstacles. Une destination sur le maillage mais inaccessible mène au point accessible le plus proche.
	const bool bHasNavMesh = BotolUnitDefaults::HasNavMesh(GetWorld());
	const EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(
		Destination,
		BotolUnitDefaults::MoveAcceptanceRadius,
		/*bStopOnOverlap*/ true,
		/*bUsePathfinding*/ bHasNavMesh,
		/*bProjectDestinationToNavigation*/ bHasNavMesh,
		/*bCanStrafe*/ false);

	if (Result != EPathFollowingRequestResult::Failed || !bHasNavMesh)
	{
		return;
	}

	if (!BotolUnitDefaults::IsUnitOnNavMesh(*this))
	{
		// L'unité elle-même n'est pas sur le NavMesh (maillage vide ou unité hors limites) : déplacement direct,
		// plutôt qu'un ordre perdu sans explication.
		AIController->MoveToLocation(
			Destination,
			BotolUnitDefaults::MoveAcceptanceRadius,
			/*bStopOnOverlap*/ true,
			/*bUsePathfinding*/ false,
			/*bProjectDestinationToNavigation*/ false,
			/*bCanStrafe*/ false);
	}
	else
	{
		UE_LOG(LogBotol, Verbose, TEXT("%s : destination hors NavMesh refusee."), *GetName());
	}
}

void ABotolUnit::CommandMoveToActor(AActor* Target)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (!AIController || !Target)
	{
		return;
	}

	// Vers un acteur, le test d'arrivée tient compte de la taille de la cible : l'unité s'arrête au contact.
	const bool bHasNavMesh = BotolUnitDefaults::HasNavMesh(GetWorld());
	const EPathFollowingRequestResult::Type Result = AIController->MoveToActor(
		Target,
		BotolUnitDefaults::MoveAcceptanceRadius,
		/*bStopOnOverlap*/ true,
		/*bUsePathfinding*/ bHasNavMesh,
		/*bCanStrafe*/ false);

	if (Result == EPathFollowingRequestResult::Failed && bHasNavMesh && !BotolUnitDefaults::IsUnitOnNavMesh(*this))
	{
		// Même repli que pour un point : l'unité n'est pas sur le NavMesh, elle rejoint la cible en ligne droite.
		AIController->MoveToActor(
			Target,
			BotolUnitDefaults::MoveAcceptanceRadius,
			/*bStopOnOverlap*/ true,
			/*bUsePathfinding*/ false,
			/*bCanStrafe*/ false);
	}
}
