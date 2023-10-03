// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WheeledVehiclePawn.h"
#include "VehiclePCG.generated.h"

UENUM(BlueprintType)
enum class EVehicleRarity : uint8
{
	Common,
	Rare,
	Master,
	Legendary
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGDEMO_API UVehiclePCG : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVehiclePCG();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Holds a pointer to the BP Vehicle class
	TSubclassOf<AWheeledVehiclePawn> VehicleBP;
	void GetVehicleBP(); // Populates VehicleBP

	// Generates random vehicle stats
	void GenerateRandomVehicle();

	void ApplyMaterials();
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
