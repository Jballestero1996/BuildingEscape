// Fill out your copyright notice in the Description page of Project Settings.

#include "grabber.h"
#include  "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"
#include "Components/InputComponent.h"

#define OUT

// Sets default values for this component's properties
Ugrabber::Ugrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void Ugrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...

	physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	playerInput = GetOwner()->FindComponentByClass<UInputComponent>();

	if (physicsHandle == nullptr) {

		UE_LOG(LogTemp, Error, TEXT("Error, Physics Handle Not Found at %s"), *(GetOwner()->GetName()));
	}

	if (playerInput == nullptr) {

		UE_LOG(LogTemp, Error, TEXT("Error, Input Handle Not Found at %s"), *(GetOwner()->GetName()));

	}

	playerInput->BindAction("Grab", IE_Pressed, this, &Ugrabber::Grab);

	playerInput->BindAction("Release", IE_Pressed, this, &Ugrabber::Release);
	
}

void Ugrabber::Grab() {

	auto hitresult = getFirstPhysicsBody();
	auto compToGrab = hitresult.GetComponent();
	auto actorHit = hitresult.GetActor();

	if (actorHit != nullptr) {
		physicsHandle->GrabComponent(compToGrab,
		NAME_None, compToGrab->GetOwner()->GetActorLocation(),
		true);


	}
	
	

}

void Ugrabber::Release() {

	physicsHandle->ReleaseComponent();

	
}

const FHitResult Ugrabber::getFirstPhysicsBody()
{
	
	/*UE_LOG(LogTemp, Warning, TEXT("Location %s, Position %s"), *playerViewPoint.ToString(), *playerRotation.ToString());*/
	//DrawDebugLine(
	//	GetWorld(),
	//	playerViewPoint,
	//	lineTracedEnd,
	//	FColor(255, 0, 0),
	//	false,
	//	0.0f,
	//	0.0f,
	//	10.0f);


	FHitResult hit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);


	AActor* actorhit = hit.GetActor();
	auto hitresult = hit.GetComponent();

	if (actorhit) {

		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *(actorhit->GetName()));
	}


	return hit;
}



FVector Ugrabber::GetReachLineEnd() {

	FVector playerViewPoint;
	FRotator playerRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerViewPoint, OUT playerRotation);

	///*UE_LOG(LogTemp, Warning, TEXT("Location %s, Position %s"), *playerViewPoint.ToString(), *playerRotation.ToString());*/

	FVector lineTracedEnd = playerViewPoint + (playerRotation.Vector() * reach);
	
	return lineTracedEnd;

}

FVector Ugrabber::GetReachLineStart() {

	FVector playerViewPoint;
	FRotator playerRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT playerViewPoint, OUT playerRotation);

	///*UE_LOG(LogTemp, Warning, TEXT("Location %s, Position %s"), *playerViewPoint.ToString(), *playerRotation.ToString());*/

	FVector lineTracedEnd = playerViewPoint + (playerRotation.Vector() * reach);

	return playerViewPoint;
}

// Called every frame
void Ugrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//// ...

	FVector lineTracedEnd = GetReachLineEnd();


	if (physicsHandle->GrabbedComponent != nullptr) {

		physicsHandle->SetTargetLocation(lineTracedEnd);
	}
}

