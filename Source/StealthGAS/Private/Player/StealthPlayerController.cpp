// Copyright Epic Games, Inc. All Rights Reserved.


#include "Public/Player/StealthPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

AStealthPlayerController::AStealthPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AStealthPlayerController::SetGenericTeamId(FGenericTeamId(2));
}

void AStealthPlayerController::SetGenericTeamId(const FGenericTeamId& NewTeamId)
{
	if (TeamId != NewTeamId)
	{
		TeamId = NewTeamId;
	}
}

void AStealthPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AStealthPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : InputMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}
