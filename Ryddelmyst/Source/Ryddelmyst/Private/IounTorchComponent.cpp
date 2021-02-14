// Fill out your copyright notice in the Description page of Project Settings.


#include "IounTorchComponent.h"
#include "Components/BoxComponent.h"


// Sets default values for this component's properties
UIounTorchComponent::UIounTorchComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// TODO: create static mesh and physics component members... who would I attach them to without the parent or a builtin RootComponent?  I guess this Component could have its own thing like RootComponent (tho probly should not use that name)
	auto* boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxComponent"));
	boxComp->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->UpdateBodySetup();
	SceneRoot = boxComp;
}

// todo: should be using USceneComponent::GetAttachParent() so we can just lean on the SetupAttachment API
void UIounTorchComponent::setOrbittedSceneComponent(USceneComponent* orbitted)
{
	OrbittedSceneComponent = orbitted;
}

// Called when the game starts
void UIounTorchComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UIounTorchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

