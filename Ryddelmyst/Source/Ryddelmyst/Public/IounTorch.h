// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "IounTorch.generated.h"

/**
 * An IounTorch is a sphere that orbits around its USceneComponent parent, wreathed in heatless firelight
 */ 
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RYDDELMYST_API AIounTorch : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AIounTorch();
	/**
	 * @return the primitive component subclass that defines the torch's physical form
	 */
	UPrimitiveComponent* getPhysicality();
	/**
	 * @return the orbit yaw mod this frame
	 */
	float getOrbitYaw();
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
	uint8 iMaxMeteors = 3;
	/**
	 * Defines the radius of the tirch's orbit around the orbitted body 
	 */
	FVector OrbitOffset;
	/**
	 * Yaw degrees the torch has rotated arounded our orbitted body 
	 */
	float OrbitYaw;
	/**
 	 * Fire particles emitted by the IounTorch
	 * TODO: emissive material!  I wanna see glowy bits 
	 */  
	UPROPERTY()
	class UParticleSystemComponent* TorchParticles;
};