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
	//Gets an array of actors who are colliding with the pressure plate
	//this can be done so maybe in other rooms you would need to add 2 or more items to open a door
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

		//callback to the blueprint  that handles the opening door routine
		openDoorPls.Broadcast();

	}
	else {
		
		//callback to the blueprint that handles closing the door
		closeDoorPls.Broadcast();
	}



}

