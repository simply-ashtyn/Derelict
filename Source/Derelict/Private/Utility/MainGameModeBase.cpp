// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/MainGameModeBase.h"

AMainGameModeBase::AMainGameModeBase()
{
	Player = nullptr;
	PlayerController = nullptr;
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
