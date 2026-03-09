// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"

#include "StealthPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class STEALTHGAS_API AStealthPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AStealthPlayerState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	
private:
	UPROPERTY(VisibleAnywhere, Category = "StealthGAS | Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
