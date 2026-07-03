#include "AI/SG_StateTreeUtility.h"

#include "StateTreeExecutionContext.h"
#include "Characters/StealthEnemyCharacter.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "AI/SG_AIController.h"
#include "StateTreeAsyncExecutionContext.h"

EStateTreeRunStatus FStateTreeSenseEnemiesTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	// have we transitioned from another state?
	if (Transition.ChangeType == EStateTreeStateChangeType::Changed)
	{
		// get the instance data
		FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

		// bind the perception updated delegate on the controller
		InstanceData.Controller->OnShooterPerceptionUpdated.BindLambda(
			[WeakContext = Context.MakeWeakExecutionContext()](AActor* SensedActor, const FAIStimulus& Stimulus)
			{
				// get the instance data inside the lambda
				const FStateTreeStrongExecutionContext StrongContext = WeakContext.MakeStrongExecutionContext();
				if (FInstanceDataType* LambdaInstanceData = StrongContext.GetInstanceDataPtr<FInstanceDataType>())
				{
					if (SensedActor->ActorHasTag(LambdaInstanceData->SenseTag))
					{
						bool bDirectLOS = false;

						// calculate the direction of the stimulus
						const FVector StimulusDir = (Stimulus.StimulusLocation - LambdaInstanceData->Character->GetActorLocation()).GetSafeNormal();

						// infer the angle from the dot product between the character facing and the stimulus direction
						const float DirDot = FVector::DotProduct(StimulusDir, LambdaInstanceData->Character->GetActorForwardVector());
						const float MaxDot = FMath::Cos(FMath::DegreesToRadians(LambdaInstanceData->DirectLineOfSightCone));

						// is the direction within our perception cone?
						if (DirDot >= MaxDot)
						{
							// run a line trace between the character and the sensed actor
							FCollisionQueryParams QueryParams;
							QueryParams.AddIgnoredActor(LambdaInstanceData->Character);
							QueryParams.AddIgnoredActor(SensedActor);

							FHitResult OutHit;

							// we have direct line of sight if this trace is unobstructed
							bDirectLOS = !LambdaInstanceData->Character->GetWorld()->LineTraceSingleByChannel(OutHit, LambdaInstanceData->Character->GetActorLocation(), SensedActor->GetActorLocation(), ECC_Visibility, QueryParams);

						}

						// check if we have a direct line of sight to the stimulus
						if (bDirectLOS)
						{
							// set the controller's target
							LambdaInstanceData->Controller->SetCurrentTarget(SensedActor);

							// set the task output
							LambdaInstanceData->TargetActor = SensedActor;

							// set the flags
							LambdaInstanceData->bHasTarget = true;
						} 
					}
				}
			}
		);

		// bind the perception forgotten delegate on the controller
		InstanceData.Controller->OnShooterPerceptionForgotten.BindLambda(
			[WeakContext = Context.MakeWeakExecutionContext()](AActor* SensedActor)
			{
				// get the instance data inside the lambda
				const FStateTreeStrongExecutionContext StrongContext = WeakContext.MakeStrongExecutionContext();
				if (FInstanceDataType* LambdaInstanceData = StrongContext.GetInstanceDataPtr<FInstanceDataType>())
				{
					bool bForget = false;

					// are we forgetting the current target?
					if (SensedActor == LambdaInstanceData->TargetActor)
					{
						bForget = true;
					}
					else 
					{
						// are we forgetting about a partial sense?
						if (!IsValid(LambdaInstanceData->TargetActor))
						{
							bForget = true;
						}
					}

					if (bForget)
					{
						// clear the target
						LambdaInstanceData->TargetActor = nullptr;
						
						LambdaInstanceData->bHasTarget = false;

						// clear the target on the controller
						LambdaInstanceData->Controller->ClearCurrentTarget();
						LambdaInstanceData->Controller->ClearFocus(EAIFocusPriority::Gameplay);
					}
				}
			}
		);
	}

	return EStateTreeRunStatus::Running;
}

void FStateTreeSenseEnemiesTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
	// have we transitioned to another state?
	if (Transition.ChangeType == EStateTreeStateChangeType::Changed)
	{
		// get the instance data
		FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

		// unbind the perception delegates
		InstanceData.Controller->OnShooterPerceptionUpdated.Unbind();
		InstanceData.Controller->OnShooterPerceptionForgotten.Unbind();
	}
}

#if WITH_EDITOR
FText FStateTreeSenseEnemiesTask::GetDescription(const FGuid& ID, FStateTreeDataView InstanceDataView, const IStateTreeBindingLookup& BindingLookup, EStateTreeNodeFormatting Formatting /*= EStateTreeNodeFormatting::Text*/) const
{
	return FText::FromString("<b>Sense Enemies</b>");
}
#endif // WITH_EDITOR