#include "Player/BotolPlayerController.h"

#include "Engine/World.h"
#include "EngineUtils.h"
#include "InputCoreTypes.h"
#include "Player/BotolCameraPawn.h"
#include "Units/BotolUnit.h"

ABotolPlayerController::ABotolPlayerController()
{
	// Curseur visible pour les tests dans l'éditeur ; sans effet sur téléphone.
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Les doigts sont lus directement : pas besoin des événements de clic/toucher par acteur,
	// qui lanceraient une trace à chaque contact.
	bEnableClickEvents = false;
	bEnableTouchEvents = false;
	bEnableMouseOverEvents = false;
	bEnableTouchOverEvents = false;
}

void ABotolPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameAndUI InputMode;
	InputMode.SetHideCursorDuringCapture(false);
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}

ABotolCameraPawn* ABotolPlayerController::GetCameraPawn() const
{
	return Cast<ABotolCameraPawn>(GetPawn());
}

float ABotolPlayerController::GetDragThreshold() const
{
	int32 ViewportX = 0;
	int32 ViewportY = 0;
	GetViewportSize(ViewportX, ViewportY);
	const float ShortSide = static_cast<float>(FMath::Min(ViewportX, ViewportY));
	return FMath::Max(DragThresholdMinPixels, DragThresholdScreenFraction * ShortSide);
}

void ABotolPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	ABotolCameraPawn* CameraPawn = GetCameraPawn();
	const UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}
	const double Now = World->GetRealTimeSeconds();

	float X1 = 0.f, Y1 = 0.f, X2 = 0.f, Y2 = 0.f;
	bool bDown1 = false, bDown2 = false;
	GetInputTouchState(ETouchIndex::Touch1, X1, Y1, bDown1);
	GetInputTouchState(ETouchIndex::Touch2, X2, Y2, bDown2);
	const FVector2D Finger1(X1, Y1);
	const FVector2D Finger2(X2, Y2);

	// --- Deux doigts : pincement pour zoomer. Un pincement n'est jamais un tap. ---
	if (bDown1 && bDown2)
	{
		const double Distance = FVector2D::Distance(Finger1, Finger2);
		if (bPinching && CameraPawn && Distance > UE_KINDA_SMALL_NUMBER && LastPinchDistance > UE_KINDA_SMALL_NUMBER)
		{
			CameraPawn->ZoomBy(static_cast<float>(LastPinchDistance / Distance));
		}
		bPinching = true;
		LastPinchDistance = Distance;
		bTapCandidate = false;
		bPrimaryDown = true;
		return;
	}

	if (bPinching)
	{
		// Fin du pincement : le doigt resté posé, quel qu'il soit, reprend le déplacement de la vue, sans saut.
		bPinching = false;
		LastPinchDistance = 0.0;
		bTapCandidate = false;
		PrimaryTouch = bDown1 ? ETouchIndex::Touch1 : ETouchIndex::Touch2;
		bDragging = bDown1 || bDown2;
		PrimaryLast = bDown1 ? Finger1 : Finger2;
	}

	const bool bPrimaryNowDown = (PrimaryTouch == ETouchIndex::Touch1) ? bDown1 : bDown2;
	const FVector2D PrimaryPosition = (PrimaryTouch == ETouchIndex::Touch1) ? Finger1 : Finger2;

	// --- Un doigt : glisser pour déplacer la vue, ou tap. ---
	if (bPrimaryNowDown)
	{
		if (!bPrimaryDown)
		{
			bPrimaryDown = true;
			bDragging = false;
			bTapCandidate = true;
			PrimaryStart = PrimaryPosition;
			PrimaryLast = PrimaryPosition;
			PrimaryDownTime = Now;
		}
		else
		{
			if (!bDragging && FVector2D::Distance(PrimaryPosition, PrimaryStart) > GetDragThreshold())
			{
				bDragging = true;
				bTapCandidate = false;
			}

			if (bDragging && CameraPawn)
			{
				FVector LastWorld;
				FVector CurrentWorld;
				if (DeprojectToGround(PrimaryLast, LastWorld) && DeprojectToGround(PrimaryPosition, CurrentWorld))
				{
					// Le point de la carte saisi au doigt reste sous le doigt.
					CameraPawn->PanBy(LastWorld - CurrentWorld);
				}
			}
			PrimaryLast = PrimaryPosition;
		}
	}
	else if (bPrimaryDown)
	{
		bPrimaryDown = false;
		if (bTapCandidate && (Now - PrimaryDownTime) <= TapMaxDuration)
		{
			HandleTap(PrimaryLast);
		}
		bDragging = false;
		bTapCandidate = false;
	}
	else if (!bDown1 && !bDown2 && WasInputKeyJustPressed(EKeys::Touch1) && WasInputKeyJustReleased(EKeys::Touch1))
	{
		// Tap si bref (ou image si lente) que l'appui et le relâchement sont arrivés dans la même image :
		// la lecture des doigts ne l'a jamais vu posé, mais les événements de touche l'ont enregistré.
		HandleTap(Finger1);
	}

	// Plus aucun doigt posé : le prochain contact redevient le doigt principal.
	if (!bDown1 && !bDown2)
	{
		PrimaryTouch = ETouchIndex::Touch1;
	}

	// --- Molette : zoom pour les tests sur PC. ---
	if (CameraPawn)
	{
		if (WasInputKeyJustPressed(EKeys::MouseScrollUp))
		{
			CameraPawn->ZoomBy(1.f - MouseWheelZoomStep);
		}
		if (WasInputKeyJustPressed(EKeys::MouseScrollDown))
		{
			CameraPawn->ZoomBy(1.f + MouseWheelZoomStep);
		}
	}
}

bool ABotolPlayerController::DeprojectToGround(const FVector2D& ScreenPosition, FVector& OutWorldPoint) const
{
	FVector RayOrigin;
	FVector RayDirection;
	if (!DeprojectScreenPositionToWorld(static_cast<float>(ScreenPosition.X), static_cast<float>(ScreenPosition.Y), RayOrigin, RayDirection))
	{
		return false;
	}

	const ABotolCameraPawn* CameraPawn = GetCameraPawn();
	const FVector::FReal GroundZ = CameraPawn ? CameraPawn->GetGroundHeight() : 0.0;
	if (FMath::IsNearlyZero(RayDirection.Z))
	{
		return false;
	}

	const FVector::FReal Distance = (GroundZ - RayOrigin.Z) / RayDirection.Z;
	if (Distance <= 0.0)
	{
		return false;
	}

	OutWorldPoint = RayOrigin + RayDirection * Distance;
	return true;
}

void ABotolPlayerController::HandleTap(const FVector2D& ScreenPosition)
{
	FHitResult Hit;
	const bool bHit = GetHitResultAtScreenPosition(ScreenPosition, ECC_Visibility, /*bTraceComplex*/ false, Hit);

	FVector GroundPoint = FVector::ZeroVector;
	bool bHasGroundPoint = false;
	ABotolUnit* TappedUnit = nullptr;

	if (bHit)
	{
		GroundPoint = Hit.ImpactPoint;
		bHasGroundPoint = true;
		TappedUnit = Cast<ABotolUnit>(Hit.GetActor());
	}
	else
	{
		bHasGroundPoint = DeprojectToGround(ScreenPosition, GroundPoint);
	}

	// Tolérance au doigt : si on a tapé juste à côté d'une de ses unités, on la prend quand même.
	// Avec une unité déjà sélectionnée, un tap au sol est d'abord un ordre : la tolérance se réduit au contact.
	if (!TappedUnit && bHasGroundPoint)
	{
		const float Radius = SelectedUnit.IsValid() ? TapSelectRadiusWhenSelected : TapSelectRadius;
		TappedUnit = FindClosestUnit(GroundPoint, Radius, PlayerTeamId);
	}

	if (TappedUnit && TappedUnit->GetTeamId() == PlayerTeamId)
	{
		SelectUnit(TappedUnit);
		return;
	}

	if (!SelectedUnit.IsValid())
	{
		return;
	}

	if (TappedUnit)
	{
		// Unité ennemie tapée : pour l'instant, on la rejoint (l'attaque arrive au jalon M3).
		SelectedUnit->CommandMoveToActor(TappedUnit);
	}
	else if (bHasGroundPoint)
	{
		SelectedUnit->CommandMoveTo(GroundPoint);
	}
}

void ABotolPlayerController::SelectUnit(ABotolUnit* Unit)
{
	if (SelectedUnit.IsValid() && SelectedUnit.Get() != Unit)
	{
		SelectedUnit->SetSelected(false);
	}
	SelectedUnit = Unit;
	if (Unit)
	{
		Unit->SetSelected(true);
	}
}

ABotolUnit* ABotolPlayerController::FindClosestUnit(const FVector& WorldPoint, float Radius, int32 TeamId) const
{
	ABotolUnit* ClosestUnit = nullptr;
	FVector::FReal ClosestDistanceSquared = FMath::Square(static_cast<FVector::FReal>(Radius));

	for (TActorIterator<ABotolUnit> It(GetWorld()); It; ++It)
	{
		ABotolUnit* Unit = *It;
		if (!Unit || Unit->GetTeamId() != TeamId)
		{
			continue;
		}
		const FVector::FReal DistanceSquared = FVector::DistSquared2D(Unit->GetActorLocation(), WorldPoint);
		if (DistanceSquared < ClosestDistanceSquared)
		{
			ClosestDistanceSquared = DistanceSquared;
			ClosestUnit = Unit;
		}
	}
	return ClosestUnit;
}
