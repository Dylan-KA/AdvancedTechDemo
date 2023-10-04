// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VehicleStatsManager.generated.h"

UENUM(BlueprintType)
enum class EVehicleRarity : uint8
{
	Common = 0,
	Rare = 1,
	Master = 2,
	Legendary = 3
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

	// Functions which apply their values to the mesh component (mesh component handles logic)
	void ApplyMassScale();
	void ApplyCentreOfMass();

	// Functions which run in the tick function and are done manually (these funcitons handle logic manually)
	void MaxTopSpeedManager();
	void FuelManager();

	// The remaining two values (TurningSpeed and BreakingStrength) are handles in the VehicleMovementComponent

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Current rarity of the vehicle
	UPROPERTY(BlueprintReadOnly)
	EVehicleRarity VehicleRarity;

	// Current stats of the vehicle

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float Acceleration = 1.0f;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float MassScale = 1.0f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float CentreOfMassOffset = 0;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float MaxFuel = 10.0f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float TopSpeed = 100;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float TurningSpeed = 1.0f;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float BreakingStrength = 1.0f;
	
};
