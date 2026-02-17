// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StealthPlayerController.generated.h"

class UInputMappingContext;

UCLASS(abstract)
class AStealthPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditDefaultsOnly, Category ="Stealth|Input|Input Mappings")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

};
