// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool ACheckpoint::ShouldTickIfViewportsOnly() const
{
	return false;
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	GenerateCheckpointPositions();

}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), MiddlePosition, 30.0f, 8, FColor::Blue, false, -1, 0, 1);
	DrawDebugSphere(GetWorld(), LeftPosition, 30.0f, 8, FColor::Green, false, -1, 0, 1);
	DrawDebugSphere(GetWorld(), RightPosition, 30.0f, 8, FColor::Orange, false, -1, 0, 1);
}

void ACheckpoint::GenerateCheckpointPositions()
{
	MiddlePosition = GetActorLocation();
	
	// Define the left and right offsets (relative to the forward vector)
	FVector LeftOffset = -GetActorForwardVector() * 500.0f;
	FVector RightOffset = GetActorForwardVector() * 500.0f;

	// Calculate the left and right positions
	LeftPosition = GetActorLocation() + LeftOffset;
	RightPosition = GetActorLocation() + RightOffset;
}