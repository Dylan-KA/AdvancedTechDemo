// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementComponent.h"
#include "ChaosVehicleMovementComponent.h"

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
	VehicleCheckpoints = VehiclePathfindingSubsystem->PopulateRaceCheckpoints();

	WheeledVehiclePawn = Cast<AWheeledVehiclePawn>(GetOwner());
	MovementComponent = GetOwner()->FindComponentByClass<UChaosVehicleMovementComponent>();
	CurrentObjective = VehicleCheckpoints[0]->GetActorLocation();
	
}

// Drive towards next checkpoint
void UEnemyMovementComponent::TickNormalDriving(float DeltaTime)
{
	//Set the current objective 
	CurrentObjective = VehicleCheckpoints[0]->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("CurrentObjective: %s"), *CurrentObjective.ToString())
	MovementComponent->SetThrottleInput(VehicleSpeed);
	// Steers the car in the direction of CurrentObjective 
	TurnTowardsDirection();
	
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

FVector UEnemyMovementComponent::CalculateDirection()
{
	FVector Direction = CurrentObjective - WheeledVehiclePawn->GetActorLocation();
	Direction.Normalize();
	return Direction;
}

void UEnemyMovementComponent::TurnTowardsDirection()
{
	FVector ActorForwardVector = WheeledVehiclePawn->GetActorForwardVector();
	FVector Direction = CalculateDirection();
	//UE_LOG(LogTemp, Warning, TEXT("Direction: %s"), *Direction.ToString())
	float DotProduct = FVector::DotProduct(ActorForwardVector, Direction);

	// Check if the dot product is positive or negative to determine left or right.
	if (DotProduct < -0.1)
	{
		// Direction is to the right of the actor.
		MovementComponent->SetThrottleInput(0.2);
		MovementComponent->SetSteeringInput(VehicleTurningSpeed);
		UE_LOG(LogTemp, Warning, TEXT("Turning RIGHT"))
	}
	else if (DotProduct > 0.1)
	{
		// Direction is to the left of the actor.
		MovementComponent->SetThrottleInput(0.2);
		MovementComponent->SetSteeringInput(-VehicleTurningSpeed);
		UE_LOG(LogTemp, Warning, TEXT("Turning LEFT"))
	}
	else
	{
		// Direction is roughly in front or behind the actor.
		MovementComponent->SetSteeringInput(0);
		UE_LOG(LogTemp, Warning, TEXT("Driving STRAIGHT"))
	}
}

// Called every frame
void UEnemyMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
	case EEnemyState::Stop:
		break;
	}

	if (VehicleCheckpoints.IsEmpty())
	{
		CurrentState = EEnemyState::Stop;
	}

}

