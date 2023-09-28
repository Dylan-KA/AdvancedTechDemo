// Fill out your copyright notice in the Description page of Project Settings.

#include "FSMStateMachine.h"
#include "FSMTransition.h"

// Sets default values for this component's properties
UFSMStateMachine::UFSMStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UFSMStateMachine::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void UFSMStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (FSMState* State : States) //For every state
	{
		for (FSMTransition* Transition : State->StateTransitions) //For every transition for that state
		{
			if (Transition->IsValid()) //if transition conditions are met
			{
				ActiveState->OnExit();						//Call the exit function of current state
				ActiveState = Transition->GetNextState();	//Set the next active state
				Transition->OnTransition();					//Call the OnTransition function
				ActiveState->OnEnter();						//Call the enter function of the new state
			}
		}	
	}
	ActiveState->Tick();
}

