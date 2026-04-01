// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "StealthPlayerController.generated.h"

class UInputMappingContext;

UCLASS(Abstract)
class AStealthPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
	
public:
	explicit AStealthPlayerController(const FObjectInitializer& ObjectInitializer);
	
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamId) override;
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	
protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditDefaultsOnly, Category ="Stealth|Input|Input Mappings")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

private:
	FGenericTeamId TeamId;
};
