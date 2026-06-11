// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SG_AIController.generated.h"

struct FAIStimulus;
class UStateTreeAIComponent;

DECLARE_DELEGATE_TwoParams(FShooterPerceptionUpdatedDelegate, AActor*, const FAIStimulus&);
DECLARE_DELEGATE_OneParam(FShooterPerceptionForgottenDelegate, AActor*);

UCLASS(Abstract)
class STEALTHGAS_API ASG_AIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	ASG_AIController();
	
	/* DELEGATES */ 
	/** Called when an AI perception has been updated. StateTree task delegate hook */
	FShooterPerceptionUpdatedDelegate OnShooterPerceptionUpdated;
	
	/** Called when an AI perception has been forgotten. StateTree task delegate hook */
	FShooterPerceptionForgottenDelegate OnShooterPerceptionForgotten;
	
	
	/* TARGETING */
	/** Sets the targeted enemy */
	UFUNCTION(BlueprintCallable, Category = "StealthGAS|AI")
	void SetCurrentTarget(AActor* Target) { TargetEnemy = Target; };
	
	/** Clears the targeted enemy */
	UFUNCTION(BlueprintCallable, Category = "StealthGAS|AI")
	void ClearCurrentTarget() { TargetEnemy = nullptr; };
	
	/** Returns the targeted enemy */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StealthGAS|AI")
	AActor* GetCurrentTarget() const { return TargetEnemy; };

	UStateTreeAIComponent* GetStateTreeAI() const { return StateTreeAI; }
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

	/** Enemy currently being targeted */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> TargetEnemy;
	
	
	/* PERCEPTION HANDLING */
	/** Called when the AI perception component updates a perception on a given actor */
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	/** Called when the AI perception component forgets a given actor */
	UFUNCTION()
	void OnPerceptionForgotten(AActor* Actor);
	
private:
	/* COMPONENTS */
	/** Runs the behavior StateTree for this NPC */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UStateTreeAIComponent* StateTreeAI;

private:
	/** Detects other actors through sight, hearing and other senses */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UAIPerceptionComponent* AIPerception;
	
};
