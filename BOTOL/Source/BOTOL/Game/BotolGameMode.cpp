#include "Game/BotolGameMode.h"

#include "BOTOL.h"
#include "Data/BotolFactionData.h"
#include "Data/BotolUnitData.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Player/BotolCameraPawn.h"
#include "Player/BotolPlayerController.h"
#include "Units/BotolUnit.h"

namespace BotolTestTeam
{
	constexpr int32 Columns = 5;
	constexpr double Spacing = 160.0;
	// Couleurs provisoires si aucune faction n'est renseignée : bleu pour le joueur, rouge pour l'IA.
	const FLinearColor PlayerFallbackColor(0.1f, 0.45f, 1.f);
	const FLinearColor EnemyFallbackColor(0.9f, 0.2f, 0.15f);
}

ABotolGameMode::ABotolGameMode()
{
	DefaultPawnClass = ABotolCameraPawn::StaticClass();
	PlayerControllerClass = ABotolPlayerController::StaticClass();
	UnitClass = ABotolUnit::StaticClass();
}

void ABotolGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (!bSpawnTestUnits)
	{
		return;
	}

	// Des unités posées à la main dans le niveau ont la priorité sur l'apparition automatique.
	if (TActorIterator<ABotolUnit>(GetWorld()))
	{
		UE_LOG(LogBotol, Log, TEXT("Unites deja presentes dans le niveau : apparition de test ignoree."));
		return;
	}

	SpawnTestTeam(PlayerFaction, 0, PlayerSpawnCenter, BotolTestTeam::PlayerFallbackColor);
	SpawnTestTeam(EnemyFaction, 1, EnemySpawnCenter, BotolTestTeam::EnemyFallbackColor);

	// La vue démarre au milieu des deux équipes.
	const FVector BattleCenter = (PlayerSpawnCenter + EnemySpawnCenter) * 0.5;
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		const APlayerController* PlayerController = It->Get();
		if (ABotolCameraPawn* CameraPawn = PlayerController ? Cast<ABotolCameraPawn>(PlayerController->GetPawn()) : nullptr)
		{
			CameraPawn->FocusOn(BattleCenter);
		}
	}
}

void ABotolGameMode::SpawnTestTeam(UBotolFactionData* Faction, int32 TeamId, const FVector& Center, const FLinearColor& FallbackColor)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	UClass* ClassToSpawn = UnitClass ? UnitClass.Get() : ABotolUnit::StaticClass();
	UBotolUnitData* UnitData = (Faction && Faction->Roster.Num() > 0) ? Faction->Roster[0].Get() : nullptr;
	const FLinearColor Color = Faction ? Faction->TeamColor : FallbackColor;

	// Chaque équipe se range en lignes, face à l'autre.
	const double Direction = (TeamId == 0) ? -1.0 : 1.0;
	const FRotator Facing(0.f, (TeamId == 0) ? 0.f : 180.f, 0.f);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int32 Index = 0; Index < TestUnitsPerTeam; ++Index)
	{
		const int32 Row = Index / BotolTestTeam::Columns;
		const int32 Column = Index % BotolTestTeam::Columns;
		const FVector Offset(
			Direction * Row * BotolTestTeam::Spacing,
			(Column - (BotolTestTeam::Columns - 1) * 0.5) * BotolTestTeam::Spacing,
			0.0);

		ABotolUnit* Unit = World->SpawnActor<ABotolUnit>(ClassToSpawn, Center + Offset, Facing, SpawnParameters);
		if (Unit)
		{
			Unit->InitUnit(UnitData, TeamId, Color);
		}
	}

	UE_LOG(LogBotol, Log, TEXT("Equipe %d : %d unites de test."), TeamId, TestUnitsPerTeam);
}
