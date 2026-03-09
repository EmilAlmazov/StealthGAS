#pragma once

#include "CoreMinimal.h"
#include "Characters/StealthBaseCharacter.h"
#include "Logging/LogMacros.h"
#include "StealthCharacter.generated.h"

struct FGameplayTag;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(abstract)
class AStealthCharacter : public AStealthBaseCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Stealth|Input|Movement")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category="Stealth|Input|Movement")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Stealth|Input|Movement")
	UInputAction* MouseLookAction;

	UPROPERTY(EditDefaultsOnly, Category="Stealth|Input|Movement")
	UInputAction* CrouchAction;
	
	// Abilities
	UPROPERTY(EditDefaultsOnly, Category="Stealth|Input|Abilities")
	UInputAction* PrimaryAction;
	UPROPERTY(EditDefaultsOnly, Category="Stealth|Input|Abilities")
	UInputAction* SecondaryAction;
	UPROPERTY(EditDefaultsOnly, Category="Stealth|Input|Abilities")
	UInputAction* TertiaryAction;
	
	void ActivateAbilities(const FGameplayTag& AbilityTag) const;
	
public:

	AStealthCharacter();	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	UFUNCTION(BlueprintCallable, Category="Stealth|Input|Movement")
	virtual void DoMove(float Right, float Forward);

	UFUNCTION(BlueprintCallable, Category="Stealth|Input|Movement")
	virtual void DoLook(float Yaw, float Pitch);

	UFUNCTION(BlueprintCallable, Category="Stealth|Input|Movement")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category="Stealth|Input|Movement")
	virtual void DoJumpEnd();
	
	virtual void DoCrouchStart();
	virtual void DoCrouchEnd();
	
	
	virtual void DoPrimaryStart();
	virtual void DoSecondaryStart();
	virtual void DoTertiaryStart();
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

