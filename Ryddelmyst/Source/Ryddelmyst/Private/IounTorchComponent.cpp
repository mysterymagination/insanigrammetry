// Fill out your copyright notice in the Description page of Project Settings.


#include "IounTorchComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values for this component's properties
UIounTorchComponent::UIounTorchComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// create root scenecomponent box that'll be the physical core of our IounTorch, and then attach it to this torch object
	auto* boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("RootBoxComponent"));
	boxComp->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	boxComp->SetCollisionProfileName(TEXT("IounTorchPresence"));
	boxComp->UpdateBodySetup();
	SceneRoot = boxComp;
	SceneRoot->SetupAttachment(this);
	// IounTorch mesh
	UStaticMeshComponent* PyramidVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TheVisibleTorch"));
	PyramidVisual->SetupAttachment(SceneRoot);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PyramidVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid"));
	if (PyramidVisualAsset.Succeeded())
	{
		PyramidVisual->SetStaticMesh(PyramidVisualAsset.Object);
		PyramidVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}
	UE_LOG(LogTemp, Warning, TEXT("UIounTorchComponent::ctor; pyramid visual rough sphere bound radius is %f"), PyramidVisual->CalcLocalBounds().SphereRadius);
	// Create a particle system that will stay on all the time
	TorchParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IounTorchParticles"));
	TorchParticles->SetupAttachment(PyramidVisual);
	TorchParticles->bAutoActivate = false;
	// Offset slighlty from bottom-center of mesh to improve visibility
	TorchParticles->SetRelativeLocation(FVector(-25.0f, 0.0f, 25.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		TorchParticles->SetTemplate(ParticleAsset.Object);
	}
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
	auto* pOrbitted = this->GetAttachParent();
	// TODO: define our pos according to attach parent
	if(pOrbitted)
	{
		UE_LOG(LogTemp, Warning, TEXT("IounTorch::TickComponent; orbitted parent is %s"), *pOrbitted->GetFName().ToString());
		UE_LOG(LogTemp, Warning, TEXT("IounTorch::TickComponent; torch parent pos is %s"), *pOrbitted->GetComponentLocation().ToString());
		UE_LOG(LogTemp, Warning, TEXT("IounTorch::TickComponent; torch pos is %s"), *GetComponentLocation().ToString());
		
		// todo: debug floating torch - should really move this into a MovementComponent thingy
		FVector NewLocation = GetComponentLocation();
		//FRotator NewRotation = GetComponentRotation();
		float RunningTime = GetWorld()->GetTimeSeconds();
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		NewLocation.Z += DeltaHeight * 20;
		UE_LOG(LogTemp, Warning, TEXT("IounTorch::TickComponent; runningtime says %f and deltaheight is %f"), RunningTime, DeltaHeight);
		//float DeltaRotation = DeltaTime * 20.0f;    //Rotate by 20 degrees per second
		//NewRotation.Yaw += 0.0f;//DeltaRotation;
		//SetWorldLocationAndRotation(NewLocation, NewRotation);
		SetWorldLocation(NewLocation);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("IounTorch::TickComponent; no parent to orbit yet"));
	}
}

