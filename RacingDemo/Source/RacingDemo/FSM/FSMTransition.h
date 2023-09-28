// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FSMState.h"

class RACINGDEMO_API FSMTransition
{
	
public:
	FSMTransition();

	virtual bool IsValid(); //Returns true if the conditions for this transition are met.
	virtual FSMState* GetNextState(); //Returns the state in this transition.
	virtual void OnTransition(); //Function to be executed when transition occurs.

private:
	FSMState* NextState = nullptr;
	
};
