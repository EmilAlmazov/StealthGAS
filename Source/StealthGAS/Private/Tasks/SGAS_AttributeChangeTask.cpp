// Copyright Emil Almazov


#include "Tasks/SGAS_AttributeChangeTask.h"

#include "AbilitySystemComponent.h"

USGAS_AttributeChangeTask* USGAS_AttributeChangeTask::ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent,
                                                                               FGameplayAttribute Attribute)
{
	if (!IsValid(AbilitySystemComponent)) return nullptr;
	
	USGAS_AttributeChangeTask* WaitForAttributeChangeTask = NewObject<USGAS_AttributeChangeTask>();
	WaitForAttributeChangeTask->ACS = AbilitySystemComponent;
	WaitForAttributeChangeTask->AttributeToListenFor = Attribute;
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangeTask, &USGAS_AttributeChangeTask::HandelAttributeChanges);
	
	return WaitForAttributeChangeTask;
}

void USGAS_AttributeChangeTask::EndTask()
{
	if (ACS.IsValid())
	{
		ACS->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}
	
	SetReadyToDestroy();
	MarkAsGarbage();
}

void USGAS_AttributeChangeTask::HandelAttributeChanges(const FOnAttributeChangeData& AttributeChangeData)
{
	OnAttributeChanged.Broadcast(AttributeChangeData.Attribute, AttributeChangeData.NewValue, AttributeChangeData.OldValue);
}
