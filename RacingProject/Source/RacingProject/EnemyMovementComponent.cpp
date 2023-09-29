// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyMovementComponent.h"

// Sets default values for this component's properties
UEnemyMovementComponent::UEnemyMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WheeledVehiclePawn = Cast<AWheeledVehiclePawn>(GetOwner());

}


// Called when the game starts
void UEnemyMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	VehiclePathfindingSubsystem = GetWorld()->GetSubsystem<UVehiclePathfindingSubsystem>();
	// Vehicle starts with all checkpoints in the race
	VehicleCheckpoints = VehiclePathfindingSubsystem->PopulateRaceCheckpoints();
	
}


void UEnemyMovementComponent::TickNormalDriving()
{
	//WheeledVehiclePawn->AddMovementInput(WheeledVehiclePawn->GetActorForwardVector(), 1,false);
	// Can use ScaleValue to change speed
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
	
	switch (CurrentState)
	{
	case EEnemyState::NormalDriving:
		TickNormalDriving();
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

