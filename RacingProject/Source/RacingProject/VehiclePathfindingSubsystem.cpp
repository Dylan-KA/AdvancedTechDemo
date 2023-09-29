// Fill out your copyright notice in the Description page of Project Settings.

#include "VehiclePathfindingSubsystem.h"
#include "EngineUtils.h"

// Populates and returns RaceCheckpoints
// This is currently not sorting the order
// it is assuming they are in-order based on the name in the outliner.
TArray<ACheckpoint*> UVehiclePathfindingSubsystem::PopulateRaceCheckpoints()
{
	for (TActorIterator<ACheckpoint> It(GetWorld()); It; ++It)
	{
		RaceCheckpoints.Add(*It);
		UE_LOG(LogTemp, Warning, TEXT("Checkpoint: %s"), *(*It)->GetActorLocation().ToString())
	}
	if (RaceCheckpoints.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("RaceCheckpoints: returning empty, no checkpoints were found"))
	}
	return RaceCheckpoints;
}
