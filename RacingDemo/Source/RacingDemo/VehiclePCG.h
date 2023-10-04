// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WheeledVehiclePawn.h"
#include "VehicleStatsManager.h"
#include "VehiclePCG.generated.h"

/**
 * This Component is responsible for generating the rarity and stats of the vehicle and populating the corresponding member variables in the VehicleStatsManager
 */
UCLASS( BlueprintType, Blueprintable )
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
	void GetVehicleClass(); // Populates VehicleBP

	// Generates random vehicle stats
	void GenerateRandomVehicle();

	// Chooses a random Vehicle rarity with weighted chances
	EVehicleRarity VehicleRarityPicker();
	
	// Chooses which Stats are good and which are bad
	TArray<bool> VehicleStatPicker(int32 NumOfGood, int32 NumOfStats);

	// Component which provides behaviour for stats during runtime
	UPROPERTY()
	UVehicleStatsManager* VehicleStatsManager;

	TArray<UObject*> OutDefaultSubobjects;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
