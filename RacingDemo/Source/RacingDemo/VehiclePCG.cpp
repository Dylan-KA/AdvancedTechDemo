// Fill out your copyright notice in the Description page of Project Settings.


#include "VehiclePCG.h"
#include "RacingGameInstance.h"
#include "Engine/SCS_Node.h"

// Sets default values for this component's properties
UVehiclePCG::UVehiclePCG()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UVehiclePCG::BeginPlay()
{
	Super::BeginPlay();

	GetVehicleClass();
	PopulateVehicleStatsManager();
	//GenerateRandomVehicle();
}

void UVehiclePCG::GenerateRandomVehicle()
{
	UE_LOG(LogTemp, Warning, TEXT("CALLED GenerateRandomVehicle()"))
	VehicleStatsManager->VehicleRarity = VehicleRarityPicker();
	UE_LOG(LogTemp, Warning, TEXT("Rarity: %d"), VehicleStatsManager->VehicleRarity)
	TArray<bool> GoodStats;
	switch (VehicleStatsManager->VehicleRarity)
	{
	case EVehicleRarity::Legendary:
		GoodStats = VehicleStatPicker(5, 6);
		UE_LOG(LogTemp, Warning, TEXT("Legendary"))
		break;
	case EVehicleRarity::Master:
		GoodStats = VehicleStatPicker(4, 6);
		UE_LOG(LogTemp, Warning, TEXT("Master"))
		break;
	case EVehicleRarity::Rare:
		GoodStats = VehicleStatPicker(3, 6);
		UE_LOG(LogTemp, Warning, TEXT("Rare"))
		break;
	case EVehicleRarity::Common:
		GoodStats = VehicleStatPicker(0, 6);
		UE_LOG(LogTemp, Warning, TEXT("Common"))
		break;
	default:
		GoodStats = VehicleStatPicker(0, 6);
		UE_LOG(LogTemp, Warning, TEXT("DEFAULT"))
		break;
	}
	/*
	VehicleStatsManager->Acceleration = GoodStats[0] ? FMath::RandRange(0.7f, 0.99f) : FMath::RandRange(0.3f, 0.69f);
	VehicleStatsManager->CentreOfMassOffset = GoodStats[1] ? FMath::RandRange(0.0f, 50.0f) : FMath::RandRange(50.0f, 100.0f);
	VehicleStatsManager->MaxFuel = GoodStats[2] ? FMath::RandRange(15.0f, 30.0f) : FMath::RandRange(5.0f, 14.99f);
	VehicleStatsManager->TopSpeed = GoodStats[3] ? FMath::RandRange(100, 300) : FMath::RandRange(50, 99);
	VehicleStatsManager->TurningSpeed = GoodStats[4] ? FMath::RandRange(0.8f, 0.99f) : FMath::RandRange(0.5f, 0.79f);
	VehicleStatsManager->BreakingStrength = GoodStats[5] ? FMath::RandRange(0.5f, 1.0f) : FMath::RandRange(0.1f, 0.5f);
	FString WeaponString = "IN PCG ";
	WeaponString += "Acceleration:      " + FString::SanitizeFloat(VehicleStatsManager->Acceleration) + "\n";
	WeaponString += "CentreOfMassOffset:     " + FString::SanitizeFloat(VehicleStatsManager->CentreOfMassOffset) + "\n";
	WeaponString += "MaxFuel:   " + FString::SanitizeFloat(VehicleStatsManager->MaxFuel) + "\n";
	WeaponString += "TopSpeed: " + FString::FromInt(VehicleStatsManager->TopSpeed) + "\n";
	WeaponString += "TurningSpeed:   " + FString::SanitizeFloat(VehicleStatsManager->TurningSpeed) + "\n";
	WeaponString += "BreakingStrength:   " + FString::SanitizeFloat(VehicleStatsManager->BreakingStrength)  + "\n";
	UE_LOG(LogTemp, Warning, TEXT("%s"), *WeaponString)
	*/
}

EVehicleRarity UVehiclePCG::VehicleRarityPicker()
{
	// Rules:
	// 50% chance of Common
	// 30% chance of Rare
	// 15% chance of Master
	// 5% chance of Legendary
	UE_LOG(LogTemp, Warning, TEXT("CALLED VehicleRarityPicker()"))
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
	UE_LOG(LogTemp, Warning, TEXT("CALLED VehicleStatPicker()"))
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

void UVehiclePCG::GetVehicleClass()
{
	if (const URacingGameInstance* GameInstance = GetWorld()->GetGameInstance<URacingGameInstance>())
	{
		VehicleBP = GameInstance->GetVehicleClass();
	}
}

void UVehiclePCG::PopulateVehicleStatsManager()
{
	auto blueprint = UBlueprint::GetBlueprintFromClass(VehicleBP);

	if (blueprint && blueprint->SimpleConstructionScript)
	{
		const TArray<USCS_Node*>& scsnodes = blueprint->SimpleConstructionScript->GetAllNodes();
		for (auto scsnode : scsnodes)
		{
			if (scsnode)
			{
				if (auto itemComponent = Cast<UVehicleStatsManager>(scsnode->ComponentTemplate))
				{
					VehicleStatsManager = itemComponent;
					UE_LOG(LogTemp, Warning, TEXT("SUCCESS found VehicleStatsManager"), )
					FString WeaponString = "";
					WeaponString += "Acceleration: " + FString::SanitizeFloat(VehicleStatsManager->Acceleration) + "\n";
					WeaponString += "CentreOfMassOffset: " + FString::SanitizeFloat(VehicleStatsManager->CentreOfMassOffset) + "\n";
					WeaponString += "MaxFuel: " + FString::SanitizeFloat(VehicleStatsManager->MaxFuel) + "\n";
					WeaponString += "TopSpeed: " + FString::FromInt(VehicleStatsManager->TopSpeed) + "\n";
					WeaponString += "TurningSpeed: " + FString::SanitizeFloat(VehicleStatsManager->TurningSpeed) + "\n";
					WeaponString += "BreakingStrength: " + FString::SanitizeFloat(VehicleStatsManager->BreakingStrength)  + "\n";
					UE_LOG(LogTemp, Warning, TEXT("%s"), *WeaponString)
				}
			}
		}
	}
	if (VehicleStatsManager == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find UVehicleStatsManager component"))
	}
}


