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

USTRUCT(BlueprintType)
struct FVehicleStats
{
	GENERATED_BODY()
public:
	
	float MassScale = 1.0f;
	FVector CentreOfMass = FVector(0,0,0);
	float Fuel = 10.0f;
	float TopSpeed = 100;
	float TurningSpeed = 1.0f;
	float BreakingStrength = 1.0f;

	/**
	 * A debug ToString function that allows the easier printing of the weapon stats.
	 * @return A string detailing the weapon stats stored in this struct.
	 */
	FString ToString() const
	{
		FString WeaponString = "";
		WeaponString += "MassScale:      " + FString::SanitizeFloat(MassScale) + "\n";
		WeaponString += "CentreOfMass:     " + CentreOfMass.ToString() + "\n";
		WeaponString += "Fuel:   " + FString::SanitizeFloat(Fuel) + "\n";
		WeaponString += "TopSpeed: " + FString::FromInt(TopSpeed) + "\n";
		WeaponString += "TurningSpeed:   " + FString::SanitizeFloat(TurningSpeed) + "\n";
		WeaponString += "BreakingStrength:   " + FString::SanitizeFloat(BreakingStrength)  + "\n";
		return WeaponString;
	}
};

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
	void GetVehicleBP(); // Populates VehicleBP

	// Generates random vehicle stats
	void GenerateRandomVehicle();

	// Chooses a random Vehicle rarity with weighted chances
	EVehicleRarity VehicleRarityPicker();

	// Current stats of the vehicle
	FVehicleStats VehicleStats;
	
	// Chooses which Stats are good and which are bad
	TArray<bool> VehicleStatPicker(int32 NumOfGood, int32 NumOfStats);
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Applies material to vehicle mesh based on rarity
	UFUNCTION(BlueprintImplementableEvent)
	void ApplyMaterials();

	// Current rarity of the vehicle
	UPROPERTY(BlueprintReadOnly)
	EVehicleRarity VehicleRarity = EVehicleRarity::Common;
	
};
