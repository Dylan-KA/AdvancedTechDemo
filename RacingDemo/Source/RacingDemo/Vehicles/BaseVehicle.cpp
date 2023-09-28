// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseVehicle.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseVehicle::ABaseVehicle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup mesh and collider
	//VehicleCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Vehicle Collider"));
	VehicleMesh = CreateDefaultSubobject<USkeletalMeshComponent>("Vehicle Mesh");
	SetRootComponent(VehicleMesh);
	//VehicleCollider->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ABaseVehicle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseVehicle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

