// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"

#include "StealthBaseCharacter.generated.h"

UCLASS(Abstract)
class STEALTHGAS_API AStealthBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AStealthBaseCharacter();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
