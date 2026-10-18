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
		PrimaryLast = Finger1;
		return;
	}

	if (bPinching)
	{
		// Fin du pincement : on repart de la position actuelle du doigt restant, sans saut de caméra.
		bPinching = false;
		LastPinchDistance = 0.0;
		bTapCandidate = false;
		bDragging = bDown1;
		PrimaryLast = Finger1;
	}

	// --- Un doigt : glisser pour déplacer la vue, ou tap. ---
	if (bDown1)
	{
		if (!bPrimaryDown)
		{
			bPrimaryDown = true;
			bDragging = false;
			bTapCandidate = true;
			PrimaryStart = Finger1;
			PrimaryLast = Finger1;
			PrimaryDownTime = Now;
		}
		else
		{
			if (!bDragging && FVector2D::Distance(Finger1, PrimaryStart) > GetDragThreshold())
			{
				bDragging = true;
				bTapCandidate = false;
			}

			if (bDragging && CameraPawn)
			{
				FVector LastWorld;
				FVector CurrentWorld;
				if (DeprojectToGround(PrimaryLast, LastWorld) && DeprojectToGround(Finger1, CurrentWorld))
				{
					// Le point de la carte saisi au doigt reste sous le doigt.
					CameraPawn->PanBy(LastWorld - CurrentWorld);
				}
			}
			PrimaryLast = Finger1;
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
	if (!TappedUnit && bHasGroundPoint)
	{
		TappedUnit = FindClosestUnit(GroundPoint, TapSelectRadius, PlayerTeamId);
	}

	if (TappedUnit && TappedUnit->GetTeamId() == PlayerTeamId)
	{
		SelectUnit(TappedUnit);
		return;
	}

	if (SelectedUnit.IsValid() && bHasGroundPoint)
	{
		// Unité ennemie tapée : pour l'instant, on se déplace vers elle (l'attaque arrive au jalon M3).
		const FVector Destination = TappedUnit ? TappedUnit->GetActorLocation() : GroundPoint;
		SelectedUnit->CommandMoveTo(Destination);
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
