// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VehicleStatsManager.generated.h"

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
	 * A debug ToString function that allows the easier printing of the vehicle stats.
	 * @return A string detailing the vehicle stats stored in this struct.
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

/**
 * This Component is responsible for storing the rarity and stats of the vehicle and managing vehicle behaviour during runtime.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGDEMO_API UVehicleStatsManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVehicleStatsManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Current stats of the vehicle
	FVehicleStats VehicleStats;

	// Current rarity of the vehicle
	UPROPERTY(BlueprintReadOnly)
	EVehicleRarity VehicleRarity = EVehicleRarity::Common;
};
