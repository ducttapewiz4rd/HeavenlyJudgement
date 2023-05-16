// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractSphere.h"
#include "InteractableActor.h"
#include "Components/SphereComponent.h"

// Sets default values
AInteractSphere::AInteractSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SphereNet = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Net"));
	SphereNet->SetupAttachment(RootComponent);

}

TArray<AActor*> AInteractSphere::GetAllTargetsInRange()
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors, InteractableActorClass);
	TArray<AActor*> TargetsInRange;


	for (AActor* Actor : Actors)
	{
		TargetsInRange.AddUnique(Actor);
	}


	return TargetsInRange;
}

// Called when the game starts or when spawned
void AInteractSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

