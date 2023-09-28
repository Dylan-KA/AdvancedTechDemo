// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FSMTransition;

class RACINGDEMO_API FSMState
{
	
public:
	FSMState();

	//State functions that will be implemented in FSMStateMachine
	virtual void OnEnter();
	virtual void Tick();
	virtual void OnExit();

	//List of transitions from this state
	TArray<FSMTransition*> StateTransitions;
	
};
