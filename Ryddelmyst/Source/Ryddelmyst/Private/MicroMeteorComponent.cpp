// Fill out your copyright notice in the Description page of Project Settings.


#include "MicroMeteorComponent.h"

// Sets default values for this component's properties
UMicroMeteorComponent::UMicroMeteorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMicroMeteorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMicroMeteorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	fLifeTimer += DeltaTime;
	if (fLifeTimer >= fMaxLifeTime)
	{
		if (!bLaunched)
		{
			MeteoricLaunch();
		}
		else
		{
			fLaunchedLifeTimer += DeltaTime;
			if (fLaunchedLifeTimer >= fMaxLaunchedLifeTime)
			{
				DestroyComponent();
			}
		}
	}
}

void UMicroMeteorComponent::MeteoricLaunch()
{
	// todo: cease the orbitting motion and take off straight on orthogonal
	// todo: fire up with fire particle fx
	bLaunched = true;
}

