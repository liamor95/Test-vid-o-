#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BotolCameraPawn.generated.h"

class USceneComponent;
class USpringArmComponent;
class UCameraComponent;

/**
 * Caméra de bataille en vue 3D isométrique, pilotée au doigt par ABotolPlayerController.
 *
 * Le pion se trouve au sol, au point regardé. La caméra est fixée au bout d'un bras incliné :
 * l'angle ne change pas, on ne peut que déplacer la vue et zoomer.
 * Par défaut, perspective avec un champ de vision étroit (rendu proche de l'isométrique) ;
 * le mode orthographique se teste avec une simple case à cocher.
 */
UCLASS()
class BOTOL_API ABotolCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	ABotolCameraPawn();

	/** Déplace la vue sur le sol (en cm, coordonnées monde), en restant dans les limites de la carte. */
	void PanBy(const FVector& WorldDelta);

	/** Place le centre de la vue sur ce point de la carte (dans les limites). */
	void FocusOn(const FVector& WorldPoint);

	/** Facteur > 1 : la caméra recule. Facteur < 1 : elle se rapproche. */
	void ZoomBy(float Factor);

	/** Hauteur du sol utilisée pour convertir un point de l'écran en point de la carte. */
	float GetGroundHeight() const { return GroundHeight; }

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "BOTOL|Camera")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "BOTOL|Camera")
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(VisibleAnywhere, Category = "BOTOL|Camera")
	TObjectPtr<UCameraComponent> Camera;

	/** Inclinaison vers le sol, en degrés. Vue isométrique classique : entre 45 et 60. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera", meta = (ClampMin = "20", ClampMax = "89"))
	float CameraPitch = 55.f;

	/** Orientation horizontale de la vue, en degrés. 45 = diagonale isométrique. Fixe pendant la partie. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera")
	float CameraYaw = 45.f;

	/** Champ de vision en perspective. Étroit = aspect isométrique, peu de déformation sur les bords. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera", meta = (ClampMin = "10", ClampMax = "90"))
	float FieldOfView = 30.f;

	/** Vraie projection orthographique (isométrique stricte) au lieu de la perspective. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera")
	bool bOrthographic = false;

	/** Distance minimale de la caméra au sol (zoom maximum), en cm. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera", meta = (ClampMin = "100"))
	float MinZoomDistance = 1200.f;

	/** Distance maximale (vue la plus large), en cm. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera", meta = (ClampMin = "100"))
	float MaxZoomDistance = 5000.f;

	/** Distance au lancement de la partie, en cm. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera", meta = (ClampMin = "100"))
	float StartZoomDistance = 2600.f;

	/** Coin minimum (X, Y) que le centre de la vue peut atteindre, en cm. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera")
	FVector2D PanLimitMin = FVector2D(-5000.0, -5000.0);

	/** Coin maximum (X, Y) que le centre de la vue peut atteindre, en cm. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera")
	FVector2D PanLimitMax = FVector2D(5000.0, 5000.0);

	/** Hauteur du sol de la carte, en cm. */
	UPROPERTY(EditAnywhere, Category = "BOTOL|Camera")
	float GroundHeight = 0.f;

private:
	void ApplyCameraSettings();
	void ApplyZoom();

	float CurrentZoomDistance = 2600.f;
};
