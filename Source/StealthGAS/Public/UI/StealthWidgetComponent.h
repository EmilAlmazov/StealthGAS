// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/WidgetComponent.h"
#include "StealthWidgetComponent.generated.h"


class UAbilitySystemComponent;
class UStealthAttributeSet;
class UStealthAbilitySystemComponent;
class AStealthBaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEALTHGAS_API UStealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;
	
private:
	TWeakObjectPtr<AStealthBaseCharacter> StealthCharacter;
	TWeakObjectPtr<UStealthAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UStealthAttributeSet> AttributeSet;
	
	void InitAbilitySystemData();
	bool IsASCInitialized() const;
	void EnsureAttributesAreReady();
	void BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;

	UFUNCTION()
	void HandleASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	UFUNCTION()
	void HandleAttributesInitialized();
};
