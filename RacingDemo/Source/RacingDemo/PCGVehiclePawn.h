// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "UProceduralComponent.h"
#include "PCGVehiclePawn.generated.h"

USTRUCT(BlueprintType)
struct FVehicleStats
{
	GENERATED_BODY()
public:

	float Acceleration = 1.0f;
	float MassScale = 1.0f;
	float CentreOfMassOffset = 0;
	float MaxFuel = 10.0f;
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
		WeaponString += "Acceleration: " + FString::SanitizeFloat(Acceleration) + "\n";
		WeaponString += "MassScale: " + FString::SanitizeFloat(MassScale) + "\n";
		WeaponString += "CentreOfMassOffset: " + FString::SanitizeFloat(CentreOfMassOffset) + "\n";
		WeaponString += "MaxFuel: " + FString::SanitizeFloat(MaxFuel) + "\n";
		WeaponString += "TopSpeed: " + FString::FromInt(TopSpeed) + "\n";
		WeaponString += "TurningSpeed: " + FString::SanitizeFloat(TurningSpeed) + "\n";
		WeaponString += "BreakingStrength: " + FString::SanitizeFloat(BreakingStrength)  + "\n";
		return WeaponString;
	}
};

UCLASS()
class RACINGDEMO_API APCGVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APCGVehiclePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Current rarity of the vehicle
	UPROPERTY(BlueprintReadOnly)
	EVehicleRarity VehicleRarity;

	// Current stats of the vehicle
	UPROPERTY(BlueprintReadOnly)
	FVehicleStats VehicleStats;

	// ProceduralComponent
	UPROPERTY()
	UProceduralComponent* ProceduralComponent;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "VehiclePCG")
	void ApplyMaterials();
	
};
