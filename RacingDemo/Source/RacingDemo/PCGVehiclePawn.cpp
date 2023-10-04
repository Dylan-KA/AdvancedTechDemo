// Fill out your copyright notice in the Description page of Project Settings.

#include "PCGVehiclePawn.h"
#include "ChaosVehicleMovementComponent.h"

// Sets default values
APCGVehiclePawn::APCGVehiclePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProceduralComponent = CreateDefaultSubobject<UProceduralComponent>("Procedural Component");
	MyVehicleMovementComponent = GetVehicleMovementComponent();
}

// Called when the game starts or when spawned
void APCGVehiclePawn::BeginPlay()
{
	Super::BeginPlay();

	ProceduralComponent->GenerateRandomVehicle(VehicleRarity, VehicleStats);
	ApplyWeightDistribution();
	CurrentFuel = VehicleStats.MaxFuelCapacity;
	ApplyMaterials();
}

void APCGVehiclePawn::UpdateFuelAmount(float DeltaTime)
{
	if (MyVehicleMovementComponent->GetForwardSpeed() > 0.0f)
	{
		CurrentFuel -= DeltaTime/10;
		//UE_LOG(LogTemp, Warning, TEXT("CurrentFuel: %f"), CurrentFuel)
	}
}

// Called every frame
void APCGVehiclePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateFuelAmount(DeltaTime);

	if (CurrentFuel <= 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of fuel"))
		MyVehicleMovementComponent->SetHandbrakeInput(1.0f);
	}
	
}

// Called to bind functionality to input
void APCGVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}
