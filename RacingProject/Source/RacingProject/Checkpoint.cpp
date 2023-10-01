// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpoint.h"
#include "EnemyMovementComponent.h"
#include "WheeledVehiclePawn.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CheckpointCollider = CreateDefaultSubobject<UBoxComponent>("Checkpoint Collision Box");
	SetRootComponent(CheckpointCollider);
	CheckpointCollider->SetBoxExtent(FVector(800,100,400));
	
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
	if (CheckpointCollider)
	{

		CheckpointCollider->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnPickupOverlap);
	}
	else
	{
		// Sometimes it can be useful to print error messages if something that shouldn't be a nullptr is a nullptr.
		UE_LOG(LogTemp, Error, TEXT("PickupCollider is null in the PickupBase class."))
	}
	
}

void ACheckpoint::OnPickupOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& HitInfo)
{
	//UE_LOG(LogTemp, Warning, TEXT("A vehicle has collided with checkpoint"))
	if (AWheeledVehiclePawn* Vehicle = Cast<AWheeledVehiclePawn>(OtherActor))
	{
		if (Vehicle->FindComponentByClass<UEnemyMovementComponent>())
		{
			if (!Vehicle->FindComponentByClass<UEnemyMovementComponent>()->VehicleCheckpoints.IsEmpty())
			{
				Vehicle->FindComponentByClass<UEnemyMovementComponent>()->VehicleCheckpoints.Remove(this);
				if (!Vehicle->FindComponentByClass<UEnemyMovementComponent>()->VehicleCheckpoints.IsEmpty())
				{
					Vehicle->FindComponentByClass<UEnemyMovementComponent>()->CurrentObjective =
						Vehicle->FindComponentByClass<UEnemyMovementComponent>()->VehicleCheckpoints[0]->GetActorLocation();
				}
			}
		}
	}
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

