// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"

#include "SG_StateTreeUtility.generated.h"

class AStealthEnemyCharacter;
class ASG_AIController;

/**
 *  Instance data struct for the Sense Enemies StateTree task
 */
USTRUCT()
struct FStateTreeSenseEnemiesInstanceData
{
	GENERATED_BODY()
	
	/** Sensing AI Controller */
	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<ASG_AIController> Controller;

	/** Sensing NPC */
	UPROPERTY(EditAnywhere, Category = Context)
	TObjectPtr<AStealthEnemyCharacter> Character;

	/** Sensed actor to target */
	UPROPERTY(EditAnywhere, Category = Output)
	TObjectPtr<AActor> TargetActor;
	
	/** True if a target was successfully sensed */
	UPROPERTY(EditAnywhere, Category = Output)
	bool bHasTarget = false;
	
	/** Tag required on sensed actors */
	UPROPERTY(EditAnywhere, Category = Parameter)
	FName SenseTag = FName("Player");
	
	/** Line of sight cone half angle to consider a full sense */
	UPROPERTY(EditAnywhere, Category = Parameter)
	float DirectLineOfSightCone = 85.0f;
};

/**
 *  StateTree task to have an NPC process AI Perceptions and sense nearby enemies
 */
USTRUCT(meta=(DisplayName="Sense Enemies", Category="StealthGAS"))
struct FStateTreeSenseEnemiesTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	/* Ensure we're using the correct instance data struct */
	using FInstanceDataType = FStateTreeSenseEnemiesInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	/** Runs when the owning state is entered */
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

	/** Runs when the owning state is ended */
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;

#if WITH_EDITOR
	virtual FText GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting = EStateTreeNodeFormatting::Text) const override;
#endif // WITH_EDITOR
};