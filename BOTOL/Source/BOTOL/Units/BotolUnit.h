#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BotolUnit.generated.h"

class UBotolUnitData;
class UStaticMeshComponent;
class UMaterialInstanceDynamic;

/**
 * Unité de bataille BOTOL.
 *
 * Optimisée pour le mobile :
 * - déplacement en mode « NavWalking » (suit le NavMesh sans balayage du sol, bien moins coûteux) ;
 * - pas de Tick d'acteur ; animation calculée seulement quand l'unité est visible ;
 * - le maillage ne gère aucune collision, seule la capsule le fait.
 *
 * Sans maillage dans ses données, l'unité s'affiche comme un cylindre provisoire à la couleur de son équipe.
 */
UCLASS()
class BOTOL_API ABotolUnit : public ACharacter
{
	GENERATED_BODY()

public:
	ABotolUnit();

	/** Applique les données, l'équipe et la couleur. À appeler juste après l'apparition de l'unité. */
	UFUNCTION(BlueprintCallable, Category = "BOTOL|Unit")
	void InitUnit(UBotolUnitData* InUnitData, int32 InTeamId, FLinearColor InTeamColor);

	/** Affiche ou masque l'anneau de sélection. */
	UFUNCTION(BlueprintCallable, Category = "BOTOL|Unit")
	void SetSelected(bool bInSelected);

	/**
	 * Ordre de déplacement vers un point. Avec un NavMesh, l'unité contourne les obstacles et une destination
	 * inaccessible est refusée ; sans NavMesh (niveau de test), elle va en ligne droite.
	 */
	UFUNCTION(BlueprintCallable, Category = "BOTOL|Unit")
	void CommandMoveTo(const FVector& Destination);

	/** Ordre de rejoindre un acteur (une unité ennemie, par exemple), même s'il bouge. S'arrête au contact. */
	UFUNCTION(BlueprintCallable, Category = "BOTOL|Unit")
	void CommandMoveToActor(AActor* Target);

	/** Sélection en jeu (au doigt). Nom distinct de UObject::IsSelected, qui concerne la sélection dans l'éditeur. */
	UFUNCTION(BlueprintPure, Category = "BOTOL|Unit")
	bool IsUnitSelected() const { return bSelected; }

	UFUNCTION(BlueprintPure, Category = "BOTOL|Unit")
	int32 GetTeamId() const { return TeamId; }

	UFUNCTION(BlueprintPure, Category = "BOTOL|Unit")
	float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintPure, Category = "BOTOL|Unit")
	UBotolUnitData* GetUnitData() const;

protected:
	virtual void BeginPlay() override;

	/** Type d'unité. Peut être réglé directement sur une unité posée dans le niveau. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Unit")
	TObjectPtr<UBotolUnitData> UnitData;

	/** Équipe : 0 = joueur, 1 = IA. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Unit")
	int32 TeamId = 0;

	/** Couleur de l'équipe (sert au cylindre provisoire). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BOTOL|Unit")
	FLinearColor TeamColor = FLinearColor(0.1f, 0.45f, 1.f);

	/** Corps provisoire, visible tant qu'aucun maillage n'est fourni par les données. */
	UPROPERTY(VisibleAnywhere, Category = "BOTOL|Unit")
	TObjectPtr<UStaticMeshComponent> PlaceholderBody;

	/** Anneau au sol affiché quand l'unité est sélectionnée. */
	UPROPERTY(VisibleAnywhere, Category = "BOTOL|Unit")
	TObjectPtr<UStaticMeshComponent> SelectionRing;

	UPROPERTY(Transient)
	TObjectPtr<UMaterialInstanceDynamic> BodyMaterial;

	UPROPERTY(Transient)
	TObjectPtr<UMaterialInstanceDynamic> RingMaterial;

	float CurrentHealth = 0.f;
	bool bSelected = false;

private:
	void ApplyUnitData();
	void ApplyColors();
};
