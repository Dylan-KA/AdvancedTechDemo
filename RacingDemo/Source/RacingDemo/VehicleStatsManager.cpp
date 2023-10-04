// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleStatsManager.h"

// Sets default values for this component's properties
UVehicleStatsManager::UVehicleStatsManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVehicleStatsManager::BeginPlay()
{
	Super::BeginPlay();

	ApplyMassScale();
	ApplyCentreOfMass();
	
}

void UVehicleStatsManager::ApplyMassScale()
{
	GetOwner()->FindComponentByClass<UStaticMeshComponent>()->BodyInstance.SetMassScale(VehicleStats.MassScale);
	UE_LOG(LogTemp, Warning, TEXT("GetBodyMass: %f"), GetOwner()->FindComponentByClass<UStaticMeshComponent>()->BodyInstance.GetBodyMass())
}

void UVehicleStatsManager::ApplyCentreOfMass()
{
	FVector NewCentreOfMass = FVector(0,0,0);
	NewCentreOfMass.X = VehicleStats.CentreOfMassOffset;
	GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetCenterOfMass(NewCentreOfMass);
	UE_LOG(LogTemp, Warning, TEXT("GetCentreOfMass: %f"), GetOwner()->FindComponentByClass<UStaticMeshComponent>()->GetCenterOfMass())
}


// Called every frame
void UVehicleStatsManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

