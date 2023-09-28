// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVehicle.h"
#include "Perception/PawnSensingComponent.h"
#include "EnemyVehicle.generated.h"

UENUM()
enum EDifficulty : uint8
{
	Easy = 0,
	Medium = 1,
	Hard = 2,
};

UCLASS()
class RACINGDEMO_API AEnemyVehicle : public ABaseVehicle
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyVehicle();
	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	TArray<ABaseVehicle*> DetectedVehicles; //List of all vehicles that have been detected

	UPROPERTY(VisibleAnywhere)
	TArray<UBoxComponent*> BoxComponents; //List of box components (one on each side of the car)

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EDifficulty> VehicleDifficulty = Easy; //Default difficulty is easy
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
