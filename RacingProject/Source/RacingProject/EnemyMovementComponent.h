// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WheeledVehiclePawn.h"
#include "Components/BoxComponent.h"
#include "VehiclePathfindingSubsystem.h"
#include "Checkpoint.h"
#include "EnemyMovementComponent.generated.h"

/**
 * An enum to hold the difficulty of the enemy vehicle.
 */
UENUM(BlueprintType)
enum class EDifficulty : uint8
{
	Easy = 0,
	Medium = 1,
	Hard = 2,
};

/**
 * An enum to hold the current state of the enemy character.
 */
UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	NormalDriving,
	Overtake,
	Defend,
	Recover,
	CatchUp
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGPROJECT_API UEnemyMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyMovementComponent();

	// Reference to the Actor as a Wheeled Vehicle Pawn
	// Used for Controlling enemy movement
	UPROPERTY()
	AWheeledVehiclePawn* WheeledVehiclePawn; 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Enemy Difficulty
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDifficulty> VehicleDifficulty = EDifficulty::Easy;

	//Current Enemy State
	UPROPERTY(EditAnywhere)
	EEnemyState CurrentState = EEnemyState::NormalDriving;
	
	//List of all vehicles that have been detected
	UPROPERTY(EditAnywhere)
	TArray<AActor*> DetectedVehicles;

	//List of box components (one on each side of the car)
	UPROPERTY(EditAnywhere)
	TArray<UBoxComponent*> BoxComponents;

	//Pathfinding Subsystem provides logic for where to travel to
	UPROPERTY()
	UVehiclePathfindingSubsystem* VehiclePathfindingSubsystem;

	//An in-order list of checkpoints that the EnemyVehicle needs to pass
	UPROPERTY(VisibleAnywhere)
	TArray<ACheckpoint*> VehicleCheckpoints;

	//Tick functions for each State
	void TickNormalDriving();	//Drive towards next checkpoint
	void TickOvertake();		//Overtake one car in front
	void TickDefend();			//Position car to block other cars from overtaking
	void TickRecover();			//Return to track after going off-course.
	void TickCatchUp();			//When really far behind, speed up.
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
