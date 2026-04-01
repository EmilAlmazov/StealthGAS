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
	virtual UAttributeSet* GetAttributeSet() const override;
	virtual void HandleDeath() override;
	virtual void HandleRespawn() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StealthGAS | AI")
	float AcceptanceRadius{500.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StealthGAS | AI")
	float MinAttackDelay{0.1f};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StealthGAS | AI")
	float MaxAttackDelay{0.5f};
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "StealthGAS | Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
