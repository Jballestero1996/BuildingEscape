// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include  "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner();

	// ...


}

float UOpenDoor::GetTotalMassOfActor() {

	float totalMass = 0.0f;
	TArray<AActor*>  overlappingActors;

	PressurePlate->GetOverlappingActors(overlappingActors);

	for (AActor* actor : overlappingActors) {

		totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return totalMass;

}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (GetTotalMassOfActor() > triggerMass) {
		//create a rotator 

		//owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		openDoorPls.Broadcast();

	}
	else {
		
		closeDoorPls.Broadcast();
	}



}

