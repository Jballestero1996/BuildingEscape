// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorStuffPls);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	UPROPERTY(BlueprintAssignable)
	FDoorStuffPls openDoorPls;

	UPROPERTY(BlueprintAssignable)
	FDoorStuffPls closeDoorPls;
private:
	
	UPROPERTY(EditAnywhere)
	float openDoorAngle = -90.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;


	UPROPERTY(EditAnywhere)
		//float delay = 1.0f;

		//float lastDoorOpenTime = 0.f;

	float triggerMass = 50.0f;

	AActor* owner;
	float GetTotalMassOfActor();

	
};


