#include "Player/BotolCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABotolCameraPawn::ABotolCameraPawn()
{
	// Aucune logique par image : la vue ne bouge que sur ordre du contrôleur.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(SceneRoot);
	CameraArm->SetUsingAbsoluteRotation(true);
	CameraArm->bDoCollisionTest = false;
	CameraArm->bEnableCameraLag = false;
	CameraArm->bUsePawnControlRotation = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	ApplyCameraSettings();
}

void ABotolCameraPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	ApplyCameraSettings();
}

void ABotolCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	// Le pion se pose au sol et ne pivote jamais : seul le bras porte l'angle de vue.
	const FVector Start = GetActorLocation();
	SetActorLocationAndRotation(FVector(Start.X, Start.Y, GroundHeight), FRotator::ZeroRotator);
	PanBy(FVector::ZeroVector);

	ApplyCameraSettings();
}

void ABotolCameraPawn::ApplyCameraSettings()
{
	CameraArm->SetRelativeRotation(FRotator(-CameraPitch, CameraYaw, 0.f));
	CurrentZoomDistance = FMath::Clamp(StartZoomDistance, MinZoomDistance, FMath::Max(MinZoomDistance, MaxZoomDistance));
	ApplyZoom();
}

void ABotolCameraPawn::PanBy(const FVector& WorldDelta)
{
	FVector Location = GetActorLocation();
	Location.X = FMath::Clamp(Location.X + WorldDelta.X, PanLimitMin.X, PanLimitMax.X);
	Location.Y = FMath::Clamp(Location.Y + WorldDelta.Y, PanLimitMin.Y, PanLimitMax.Y);
	Location.Z = GroundHeight;
	SetActorLocation(Location);
}

void ABotolCameraPawn::FocusOn(const FVector& WorldPoint)
{
	SetActorLocation(FVector(WorldPoint.X, WorldPoint.Y, GroundHeight));
	PanBy(FVector::ZeroVector);
}

void ABotolCameraPawn::ZoomBy(float Factor)
{
	if (Factor <= 0.f)
	{
		return;
	}
	CurrentZoomDistance = FMath::Clamp(CurrentZoomDistance * Factor, MinZoomDistance, FMath::Max(MinZoomDistance, MaxZoomDistance));
	ApplyZoom();
}

void ABotolCameraPawn::ApplyZoom()
{
	if (bOrthographic)
	{
		// Largeur visible équivalente à celle de la perspective à la même distance.
		const float OrthoWidth = 2.f * CurrentZoomDistance * FMath::Tan(FMath::DegreesToRadians(FieldOfView * 0.5f));
		Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
		Camera->SetOrthoWidth(OrthoWidth);
		// En orthographique, la distance ne change pas l'image : on garde la caméra loin pour ne rien couper.
		CameraArm->TargetArmLength = MaxZoomDistance;
	}
	else
	{
		Camera->SetProjectionMode(ECameraProjectionMode::Perspective);
		Camera->SetFieldOfView(FieldOfView);
		CameraArm->TargetArmLength = CurrentZoomDistance;
	}
}
