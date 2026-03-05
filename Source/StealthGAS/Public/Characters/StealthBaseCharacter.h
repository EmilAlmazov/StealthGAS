// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

#include "StealthBaseCharacter.generated.h"

class UGameplayEffect;
class UGameplayAbility;

UCLASS(Abstract)
class STEALTHGAS_API AStealthBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AStealthBaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	void GiveStartupAbilities();
	void InitializeAttributes() const;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StealthGAS | Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "StealthGAS | Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;
};
