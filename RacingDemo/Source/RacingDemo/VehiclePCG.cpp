// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiclePCG.h"

#include "RacingGameInstance.h"

// Sets default values for this component's properties
UVehiclePCG::UVehiclePCG()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UVehiclePCG::BeginPlay()
{
	Super::BeginPlay();

	GenerateRandomVehicle();
	UE_LOG(LogTemp, Warning, TEXT("Vehicle Rarity: %d"), (int32)VehicleRarity)
	UE_LOG(LogTemp, Warning, TEXT("Vehicle Stats: %s"), *VehicleStats.ToString())
	
}

void UVehiclePCG::GenerateRandomVehicle()
{
	VehicleRarity = VehicleRarityPicker();
	TArray<bool> GoodStats;
	switch (VehicleRarity)
	{
	case EVehicleRarity::Legendary:
		GoodStats = VehicleStatPicker(5, 6);
		break;
	case EVehicleRarity::Master:
		GoodStats = VehicleStatPicker(4, 6);
		break;
	case EVehicleRarity::Rare:
		GoodStats = VehicleStatPicker(3, 6);
		break;
	default:
		GoodStats = VehicleStatPicker(0, 6);
		break;
	}

	VehicleStats.MassScale = GoodStats[0] ? FMath::RandRange(0.8f, 1.0f) : FMath::RandRange(1.0f, 5.0f);
	//VehicleStats.CentreOfMass = GoodStats[1] ? FMath::RandRange(0.05f, 0.2f) : FMath::RandRange(0.2f, 1.0f);
	VehicleStats.Fuel = GoodStats[2] ? FMath::RandRange(15.0f, 30.0f) : FMath::RandRange(5.0f, 15.0f);
	VehicleStats.TopSpeed = GoodStats[3] ? FMath::RandRange(100, 300) : FMath::RandRange(50, 100);
	VehicleStats.TurningSpeed = GoodStats[4] ? 1.0f : FMath::RandRange(0.5f, 1.0f);
	
}

EVehicleRarity UVehiclePCG::VehicleRarityPicker()
{
	// Rules:
	// 50% chance of Common
	// 30% chance of Rare
	// 15% chance of Master
	// 5% chance of Legendary
	const float RandPercent = FMath::RandRange(0.0f, 1.0f);
	
	if (RandPercent <= 0.5f)
	{
		return EVehicleRarity::Common;
	}
	if (RandPercent <= 0.8f)
	{
		return EVehicleRarity::Rare;
	}
	if (RandPercent <= 0.95f)
	{
		return EVehicleRarity::Master;
	}
	
	return EVehicleRarity::Legendary;
}

TArray<bool> UVehiclePCG::VehicleStatPicker(int32 NumOfGood, int32 NumOfStats)
{
	// Fill the array with the correct number of good and bad stats.
	TArray<bool> GoodStats;
	for (int32 i = 0; i < NumOfStats; i++)
	{
		// Ternary condition: Will add true if I < NumOfGood otherwise add false.
		GoodStats.Add(i < NumOfGood ? true : false);
	}

	// Array shuffling algorithm.
	for (int32 i = 0; i < GoodStats.Num(); i++)
	{
		// Get a random index from the GoodStats array.
		const int32 RandIndex = FMath::RandRange(0, GoodStats.Num() - 1);
		// Then swap the item at that random index with the item in the i index.
		const bool Temp = GoodStats[i];
		GoodStats[i] = GoodStats[RandIndex];
		GoodStats[RandIndex] = Temp;
	}

	return GoodStats;
}

// Called every frame
void UVehiclePCG::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UVehiclePCG::GetVehicleBP()
{
	VehicleBP = GetWorld()->GetGameInstance<URacingGameInstance>()->GetVehicleClass();
}


