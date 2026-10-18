#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BotolPlayerController.generated.h"

class ABotolCameraPawn;
class ABotolUnit;

/**
 * Contrôles tactiles de bataille.
 *
 * - Un doigt qui glisse : déplace la vue (le point de la carte reste sous le doigt).
 * - Deux doigts qui s'écartent ou se rapprochent : zoom.
 * - Tap sur une de ses unités : la sélectionne. Tap au sol avec une unité sélectionnée : ordre de déplacement.
 *
 * Dans l'éditeur, la souris imite un doigt (bUseMouseForTouch) et la molette zoome.
 * Les doigts sont lus directement à chaque image : aucun asset d'entrée n'est nécessaire.
 */
UCLASS()
class BOTOL_API ABotolPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABotolPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	/** Équipe contrôlée par le joueur. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Touch")
	int32 PlayerTeamId = 0;

	/** Déplacement minimum du doigt, en pixels, pour qu'un appui devienne un glissement. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Touch", meta = (ClampMin = "1"))
	float DragThresholdMinPixels = 12.f;

	/** Même seuil exprimé en part du petit côté de l'écran (s'adapte à la densité de pixels). */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Touch", meta = (ClampMin = "0", ClampMax = "0.2"))
	float DragThresholdScreenFraction = 0.015f;

	/** Durée maximale d'un appui pour qu'il compte comme un tap, en secondes. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Touch", meta = (ClampMin = "0.05"))
	float TapMaxDuration = 0.5f;

	/** Rayon de tolérance autour du doigt pour attraper une unité, en cm (les doigts sont imprécis). */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Touch", meta = (ClampMin = "0"))
	float TapSelectRadius = 120.f;

	/** Même tolérance quand une unité est déjà sélectionnée : réduite, pour qu'un tap au sol reste un ordre. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Touch", meta = (ClampMin = "0"))
	float TapSelectRadiusWhenSelected = 50.f;

	/** Pas de zoom par cran de molette (test sur PC). */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Touch", meta = (ClampMin = "0.01", ClampMax = "0.5"))
	float MouseWheelZoomStep = 0.1f;

private:
	void OnTouchPressed(ETouchIndex::Type FingerIndex, FVector Location);
	ABotolCameraPawn* GetCameraPawn() const;
	bool DeprojectToGround(const FVector2D& ScreenPosition, FVector& OutWorldPoint) const;
	float GetDragThreshold() const;
	void HandleTap(const FVector2D& ScreenPosition);
	void SelectUnit(ABotolUnit* Unit);
	ABotolUnit* FindClosestUnit(const FVector& WorldPoint, float Radius, int32 TeamId) const;

	TWeakObjectPtr<ABotolUnit> SelectedUnit;

	/** Doigt qui pilote le déplacement de la vue (change si le premier doigt se lève pendant un pincement). */
	ETouchIndex::Type PrimaryTouch = ETouchIndex::Touch1;

	bool bPrimaryDown = false;
	bool bDragging = false;
	bool bTapCandidate = false;
	FVector2D PrimaryStart = FVector2D::ZeroVector;
	FVector2D PrimaryLast = FVector2D::ZeroVector;
	double PrimaryDownTime = 0.0;

	bool bPinching = false;
	double LastPinchDistance = 0.0;

	/** Position du dernier appui de Touch1, lue dans l'événement d'appui lui-même. */
	FVector2D Touch1PressPosition = FVector2D::ZeroVector;

	/** Heure réelle de l'image précédente, pour mesurer les images lentes. */
	double LastTickRealTime = 0.0;
};
