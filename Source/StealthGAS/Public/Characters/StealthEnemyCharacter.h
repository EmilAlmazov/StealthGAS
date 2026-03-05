// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "StealthBaseCharacter.h"
#include "StealthEnemyCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class STEALTHGAS_API AStealthEnemyCharacter : public AStealthBaseCharacter
{
	GENERATED_BODY()

public:
	AStealthEnemyCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "StealthGAS | Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
