// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API Ugrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Ugrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private: 

	float reach = 150.0f;

	UInputComponent* playerInput = nullptr;
	UPhysicsHandleComponent* physicsHandle = nullptr;

	void Grab();

	const FHitResult getFirstPhysicsBody();

	void Release();

	FVector GetReachLineEnd();

	FVector GetReachLineStart();
	
};
