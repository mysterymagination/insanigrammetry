// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "OrbitMovementComponent.h"
#include "IounTorch.generated.h"

/**
 * An IounTorch is a sphere that orbits around its UPrimitiveComponent parent, wreathed in heatless firelight
 */ 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RYDDELMYST_API AIounTorch : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AIounTorch();
	/**
	 * @return pointer to the UOrbitMovementComponent that controls our orbit motion
	 */
	UOrbitMovementComponent* getOrbitController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/**
	 * Interval in seconds we should wait before spawning a meteor
	 */
	UPROPERTY(EditAnywhere)
	float fMeteorSpawnInterval = 3.0f;
	/**
	 * Incrementing timer marking the time since component inception or last meteor spawn
	 */
	float fMeteorSpawnTimer = 0.0f;
	/**
	 * The number of meteors we have spawned
	 */
	uint8 iMeteorCount = 0;
	/**
	 * The max number of meteors we allow to spawn 
	 */
	UPROPERTY(EditAnywhere)
	uint8 iMaxMeteors = 3;
	/**
 	 * Fire particles emitted by the IounTorch
	 * TODO: emissive material!  Neon bloom!  I wanna see glowy bits 
	 */  
	UPROPERTY()
	class UParticleSystemComponent* TorchParticles;
	/**
	 * Controls the torch's orbit motion around an attached body
	 */
	UPROPERTY(VisibleAnywhere)
	class UOrbitMovementComponent* OrbitMotion;
};
