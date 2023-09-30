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

void UEnemyMovementComponent::TickNormalDriving(float DeltaTime)
{
	// Rotated towards destination
	FVector Direction = CurrentObjective - WheeledVehiclePawn->GetActorLocation();
	Direction.Normalize(); // Normalize the direction vector to get a unit vector
	UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString());
	FRotator NewRotation = Direction.Rotation();
	NewRotation = FRotator(0,NewRotation.Yaw,0);
	UE_LOG(LogTemp, Warning, TEXT("NewRotation: %s"), *NewRotation.ToString());
	//SkeletalMeshComponent->AddWorldRotation(NewRotation, false, nullptr, ETeleportType::TeleportPhysics);

	// Move forwards (add force is being used like a thrust boost not continuous speed)
	if (bIsAccelerating)
	{
		SkeletalMeshComponent->AddWorldRotation(NewRotation, false, nullptr, ETeleportType::TeleportPhysics);
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
	
	if (bIsAccelerating)
	{
		AccelerationTimer -= DeltaTime;
	}
	if (AccelerationTimer <= 0.0f)
	{
		bIsAccelerating = false;
		AccelerationTimer = MaxAccelerationTime;
		UE_LOG(LogTemp, Warning, TEXT("Stopped Acclerating"))
	}
	
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

