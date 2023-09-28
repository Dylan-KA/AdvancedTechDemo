// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class RACINGPROJECT_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();
	virtual bool ShouldTickIfViewportsOnly() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Positions of the checkpoint including width of road
	UPROPERTY(EditAnywhere)
	FVector LeftPosition;	//Left bound of the checkpoint
	UPROPERTY(EditAnywhere)
	FVector MiddlePosition; //Actual position of the checkpoint
	UPROPERTY(EditAnywhere)
	FVector RightPosition;	//Right bound of the checkpoint

private:
	void GenerateCheckpointPositions();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
