// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Checkpoint.h"
#include "VehiclePathfindingSubsystem.generated.h"

/**
 * Pathfinding Subsystem provides logic for where to travel to
 */
UCLASS()
class RACINGPROJECT_API UVehiclePathfindingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<ACheckpoint*> RaceCheckpoints;

public:
	// Populates and returns RaceCheckpoints
	TArray<ACheckpoint*> PopulateRaceCheckpoints();

	// Based on current position at checkpoint, determine where (how far left or right)
	// if there is another checkpoint to travel to
	// in the next checkpoint to aim to travel to
	FVector ArrivedAtCheckpoint(FVector CurrentPosition, ACheckpoint* ArrivedCheckpoint, TArray<ACheckpoint*> VehicleCheckpoints);
	
};
