#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BotolGameMode.generated.h"

class ABotolUnit;
class UBotolFactionData;

/**
 * Mode de jeu de bataille BOTOL.
 *
 * Caméra isométrique + contrôles tactiles. Pour tester tout de suite, il fait apparaître deux équipes
 * d'unités si le niveau n'en contient aucune : équipe 0 (joueur) contre équipe 1 (IA).
 */
UCLASS()
class BOTOL_API ABotolGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABotolGameMode();

protected:
	virtual void BeginPlay() override;

	/** Faction du joueur pour la bataille de test (Aquiloris pour le premier prototype). Vide = unités provisoires. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Test")
	TObjectPtr<UBotolFactionData> PlayerFaction;

	/** Faction de l'IA pour la bataille de test (Noxéens pour le premier prototype). Vide = unités provisoires. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Test")
	TObjectPtr<UBotolFactionData> EnemyFaction;

	/** Fait apparaître des unités de test si le niveau n'en contient aucune. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Test")
	bool bSpawnTestUnits = true;

	/** Nombre d'unités par équipe. Sert aussi aux mesures de performance sur téléphone (jalon M8). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Test", meta = (ClampMin = "1", ClampMax = "200"))
	int32 TestUnitsPerTeam = 5;

	/** Centre d'apparition de l'équipe du joueur, en cm. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Test")
	FVector PlayerSpawnCenter = FVector(-800.0, 0.0, 100.0);

	/** Centre d'apparition de l'équipe IA, en cm. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Test")
	FVector EnemySpawnCenter = FVector(800.0, 0.0, 100.0);

	/** Classe d'unité à faire apparaître (un Blueprint enfant de BotolUnit, par exemple). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Test")
	TSubclassOf<ABotolUnit> UnitClass;

private:
	void SpawnTestTeam(UBotolFactionData* Faction, int32 TeamId, const FVector& Center, const FLinearColor& FallbackColor);
};
