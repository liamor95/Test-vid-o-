#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BotolUnitData.generated.h"

class USkeletalMesh;
class UAnimInstance;

/**
 * Données d'un type d'unité. Un type d'unité = un Data Asset, créé dans l'éditeur
 * (Content Browser > clic droit > Miscellaneous > Data Asset > BotolUnitData).
 *
 * Les valeurs par défaut sont des valeurs de TEST, pas de l'équilibrage validé.
 */
UCLASS(BlueprintType)
class BOTOL_API UBotolUnitData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	/** Nom affiché au joueur. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Unit")
	FText DisplayName;

	/** Points de vie maximum (valeur de test). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Stats", meta = (ClampMin = "1"))
	float MaxHealth = 100.f;

	/** Vitesse de déplacement en cm/s (valeur de test). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Stats", meta = (ClampMin = "0"))
	float MoveSpeed = 300.f;

	/** Dégâts par attaque (valeur de test, utilisée à partir du jalon M3). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Stats", meta = (ClampMin = "0"))
	float AttackDamage = 10.f;

	/** Portée d'attaque en cm (valeur de test, jalon M3). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Stats", meta = (ClampMin = "0"))
	float AttackRange = 150.f;

	/** Secondes entre deux attaques (valeur de test, jalon M3). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Stats", meta = (ClampMin = "0.05"))
	float AttackCooldown = 1.f;

	/** Maillage animé de l'unité. Vide = cylindre provisoire coloré à la couleur de l'équipe. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Visual")
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	/** Animation Blueprint associé au maillage (optionnel). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BOTOL|Visual")
	TSubclassOf<UAnimInstance> AnimClass;
};
