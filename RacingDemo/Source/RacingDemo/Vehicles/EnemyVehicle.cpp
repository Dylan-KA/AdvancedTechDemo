// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyVehicle.h"
#include "Components/BoxComponent.h"

// Sets default values
AEnemyVehicle::AEnemyVehicle()
{
	
	UBoxComponent* FrontBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Front Box"));
	FrontBox->SetupAttachment(GetRootComponent());
	FrontBox->AddLocalOffset(FVector(400,0,0));
	FrontBox->SetWorldScale3D(FVector(6,8,2));
	BoxComponents.Add(FrontBox);
	
	UBoxComponent* BackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Back Box"));
	BackBox->SetupAttachment(GetRootComponent());
	BackBox->AddLocalOffset(FVector(-500,0,0));
	BackBox->SetWorldScale3D(FVector(6,8,2));
	BoxComponents.Add(BackBox);
	
}

// Called when the game starts or when spawned
void AEnemyVehicle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
