// Copyright Emil Almazov


#include "AI/SG_AIController.h"

#include "Characters/StealthEnemyCharacter.h"
#include "Components/StateTreeAIComponent.h"
#include "Perception/AIPerceptionComponent.h"


ASG_AIController::ASG_AIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// create the StateTree component
	StateTreeAI = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAI"));
	StateTreeAI->SetStartLogicAutomatically(false);

	// create the AI perception component. It will be configured in BP
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	// subscribe to the AI perception delegates
	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ASG_AIController::OnPerceptionUpdated);
	AIPerception->OnTargetPerceptionForgotten.AddDynamic(this, &ASG_AIController::OnPerceptionForgotten);
}

/* PROTECTED */
void ASG_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// ensure we're possessing an NPC
	if (AStealthEnemyCharacter* NPC = Cast<AStealthEnemyCharacter>(InPawn))
	{
		// start AI logic
		StateTreeAI->StartLogic();
	}
}

void ASG_AIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	// pass the data to the StateTree delegate hook
	OnShooterPerceptionUpdated.ExecuteIfBound(Actor, Stimulus);
}

void ASG_AIController::OnPerceptionForgotten(AActor* Actor)
{
	// pass the data to the StateTree delegate hook
	OnShooterPerceptionForgotten.ExecuteIfBound(Actor);
}

