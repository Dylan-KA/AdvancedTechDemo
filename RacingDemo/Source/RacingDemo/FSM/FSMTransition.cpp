// Fill out your copyright notice in the Description page of Project Settings.


#include "FSMTransition.h"

FSMTransition::FSMTransition()
{
	
}

bool FSMTransition::IsValid()
{
	return true;
}

FSMState* FSMTransition::GetNextState()
{
	return NextState;
}

void FSMTransition::OnTransition()
{
	return;
}


