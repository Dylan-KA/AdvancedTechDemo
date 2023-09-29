// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "VehiclePathfindingSubsystem.h"
#include "EnemyMovementComponent.generated.h"

UENUM()
enum EDifficulty : uint8
{
	Easy = 0,
	Medium = 1,
	Hard = 2,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RACINGPROJECT_API UEnemyMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Enemy Difficulty
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDifficulty> VehicleDifficulty = Easy;

	//List of all vehicles that have been detected
	UPROPERTY(EditAnywhere)
	TArray<AActor*> DetectedVehicles;

	//List of box components (one on each side of the car)
	UPROPERTY(EditAnywhere)
	TArray<UBoxComponent*> BoxComponents;

	UPROPERTY()
	UVehiclePathfindingSubsystem* VehiclePathfindingSubsystem;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
