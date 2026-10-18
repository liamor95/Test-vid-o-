#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BotolFactionData.generated.h"

class UBotolUnitData;

/**
 * Données d'une faction. Ajouter une faction = créer un Data Asset de ce type,
 * sans toucher au code. Premier prototype : Aquiloris et Noxéens.
 */
UCLASS(BlueprintType)
class BOTOL_API UBotolFactionData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Identifiant stable utilisé par le code (ex. Aquiloris, Noxeens). Jamais affiché. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Faction")
	FName FactionId;

	/** Nom affiché au joueur. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Faction")
	FText DisplayName;

	/** Couleur de lisibilité en bataille. Provisoire tant que la direction artistique ne l'a pas validée. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Faction")
	FLinearColor TeamColor = FLinearColor::White;

	/** Types d'unités disponibles pour cette faction. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Faction")
	TArray<TObjectPtr<UBotolUnitData>> Roster;
};
