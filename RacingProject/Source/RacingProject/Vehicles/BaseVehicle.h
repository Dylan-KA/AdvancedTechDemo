// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RacingProject/Checkpoint.h"
#include "BaseVehicle.generated.h"

class UBoxComponent;
class UCameraComponent;

UCLASS()
class RACINGPROJECT_API ABaseVehicle : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float CurrentSpeed = 0.0f;
	float Acceleration = 1.0f;
	float MaxSpeed = 100.0f;

	//The Mesh of the vehicle
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* VehicleMesh;

	//The Collider of the vehicle
	UPROPERTY(EditAnywhere)
	UBoxComponent* VehicleCollider;
	
	//The last checkpoint that has been passed
	UPROPERTY()
	ACheckpoint* CurrentCheckpoint;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
