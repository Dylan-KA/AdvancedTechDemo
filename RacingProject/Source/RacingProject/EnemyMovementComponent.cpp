// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementComponent.h"

// Sets default values for this component's properties
UEnemyMovementComponent::UEnemyMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}

// Called when the game starts
void UEnemyMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	VehiclePathfindingSubsystem = GetWorld()->GetSubsystem<UVehiclePathfindingSubsystem>();
	// Vehicle starts with all checkpoints in the race
	VehicleCheckpoints = VehiclePathfindingSubsystem->PopulateRaceCheckpoints();

	WheeledVehiclePawn = Cast<AWheeledVehiclePawn>(GetOwner());
	SkeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	CurrentObjective = VehicleCheckpoints[0]->GetActorLocation();
	
}

// Drive towards next checkpoint
void UEnemyMovementComponent::TickNormalDriving(float DeltaTime)
{
	FVector Direction = CurrentObjective - WheeledVehiclePawn->GetActorLocation();
	Direction.Normalize();

	// Calculate the rotation to face the target direction
	FRotator TargetRotation = Direction.Rotation();
	TargetRotation.Pitch = 0; // Ensure you only rotate around the Yaw axis
	TargetRotation.Roll = 0; // Ensure you only rotate around the Yaw axis

	// Interpolate between the current rotation and the target rotation
	FRotator CurrentRotation = SkeletalMeshComponent->GetComponentRotation();
	FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationInterpSpeed);

	// Apply the new rotation to the mesh component
	if (bIsRotating)
	{
		SkeletalMeshComponent->SetWorldRotation(NewRotation, false, nullptr, ETeleportType::TeleportPhysics);
	}
	// Check if we are close enough to the target direction to stop rotating
	if (FMath::IsNearlyEqual(CurrentRotation.Yaw, TargetRotation.Yaw, RotationTolerance))
	{
		bIsRotating = false; // Set a flag to stop further rotation if needed
		UE_LOG(LogTemp, Warning, TEXT("Stopped rotating"))
	} else
	{
		bIsRotating = true;
		UE_LOG(LogTemp, Warning, TEXT("Started rotating"))
	}
	
	// Move forwards (add force is being used like a thrust boost not continuous speed)
	if (bIsAccelerating)	
	{
		SkeletalMeshComponent->AddForce(WheeledVehiclePawn->GetActorForwardVector()*10'000, NAME_None, true);
	}

	return;
}

void UEnemyMovementComponent::TickOvertake()
{
	return;
}

void UEnemyMovementComponent::TickDefend()
{
	return;
}

void UEnemyMovementComponent::TickRecover()
{
	return;
}

void UEnemyMovementComponent::TickCatchUp()
{
	return;
}


// Called every frame
void UEnemyMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Toggling between a short burst of acceleration and a short duration of the car rolling forwards
	if (bIsAccelerating)
	{
		AccelerationTimer -= DeltaTime;
		if (AccelerationTimer <= 0.0f)
		{
			bIsAccelerating = false;
			AccelerationTimer = MaxAccelerationTime;
			//UE_LOG(LogTemp, Warning, TEXT("Stopped Acclerating"))
		}
	} else
	{
		RollTimer -= DeltaTime;
		if (RollTimer <= 0.0f)
		{
			bIsAccelerating = true;
			RollTimer = MaxRollTime;
			//UE_LOG(LogTemp, Warning, TEXT("Starting Acclerating"))
		}
	}

	// Calling State Tick Functions 
	switch (CurrentState)
	{
	case EEnemyState::NormalDriving:
		TickNormalDriving(DeltaTime);
		break;
	case EEnemyState::Overtake:
		TickOvertake();
		break;
	case EEnemyState::Defend:
		TickDefend();
		break;
	case EEnemyState::Recover:
		TickRecover();
		break;
	case EEnemyState::CatchUp:
		TickCatchUp();
		break;
	}
	
}

