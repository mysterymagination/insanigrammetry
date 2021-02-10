// Fill out your copyright notice in the Description page of Project Settings.


#include "MollyPawnMovementComponent.h"

void UMollyPawnMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Make sure that everything is still valid, and that we are allowed to move.
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	// Get (and then clear) the movement vector that we set in ACollidingPawn::Tick
	FVector InputVector = ConsumeInputVector().GetClampedToMaxSize(1.0f);
	UE_LOG(LogTemp, Warning, TEXT("MollyPawnMovementComponent::TickComponent; input vector is %s"), *InputVector.ToString());
	FVector DesiredMovementThisFrame = InputVector * DeltaTime * 50.0f;
	UE_LOG(LogTemp, Warning, TEXT("MollyPawnMovementComponent::TickComponent; init desired movement vector is %s"), *DesiredMovementThisFrame.ToString());
	if (!DesiredMovementThisFrame.IsNearlyZero())
	{
		// update continuous movement time, clamping at ceil of 0.3 seconds (to cap our acceleration below)
		fMoveTime += DeltaTime;
		fMoveTime = FMath::Clamp(fMoveTime, 0.0f, 0.3f);
		UE_LOG(LogTemp, Warning, TEXT("MollyPawnMovementComponent::TickComponent; fMoveTime is %f"), fMoveTime);
	
		// juice our desired movement this frame by our continuous movement time, to simulate acceleration
		DesiredMovementThisFrame *= fMoveTime * 100.0f;
		UE_LOG(LogTemp, Warning, TEXT("MollyPawnMovementComponent::TickComponent; final desired movement vector is %s"), *DesiredMovementThisFrame.ToString());
	

		FHitResult Hit;
		SafeMoveUpdatedComponent(DesiredMovementThisFrame, UpdatedComponent->GetComponentRotation(), true, Hit);

		// If we bumped into something, try to slide along it
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(DesiredMovementThisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
		}
	}
	else 
	{
		fMoveTime = 0.0f;
	}
}

float UMollyPawnMovementComponent::getMoveTime()
{
	return fMoveTime;
}
