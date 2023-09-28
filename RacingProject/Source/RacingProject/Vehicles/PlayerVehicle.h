// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVehicle.h"
#include "PlayerVehicle.generated.h"

UCLASS()
class RACINGDEMO_API APlayerVehicle : public ABaseVehicle
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerVehicle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The 3rd person camera
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
