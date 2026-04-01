// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"

#include "StealthBaseCharacter.generated.h"

struct FOnAttributeChangeData;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class STEALTHGAS_API AStealthBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AStealthBaseCharacter();
	
	// Server Replication
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	// AI Perception
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamId) override {} // empty as the team ID should not be set by any code outside of PossessedBy
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	virtual void PossessedBy(AController* NewController) override;
	
	// Ability System
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const { return nullptr; }
	
	bool IsAlive() const { return bAlive; }
	void SetAlive(const bool bAliveStatus) { bAlive = bAliveStatus; }
	
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;
	
	UFUNCTION(BlueprintCallable, Category="StealthGAS | Death")
	virtual void HandleRespawn();
	
	UFUNCTION(BlueprintCallable, Category="StealthGAS | Death")
	void ResetAttributes();
	
protected:
	void GiveStartupAbilities();
	void InitializeAttributes() const;
	
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);
	virtual void HandleDeath();
	
	void BindToHealthDelegate();
	
private:
	FGenericTeamId TeamId;
	
	UPROPERTY(EditDefaultsOnly, Category = "StealthGAS | Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "StealthGAS | Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "StealthGAS | Effects")
	TSubclassOf<UGameplayEffect> ResetAttributesEffect;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated)
	bool bAlive;
};
