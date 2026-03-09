// Copyright Emil Almazov


#include "UI/StealthWidgetComponent.h"

#include "AbilitySystem/StealthAbilitySystemComponent.h"
#include "AbilitySystem/StealthAttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/StealthBaseCharacter.h"
#include "UI/SGAS_AttributeWidget.h"


void UStealthWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilitySystemData();
	if (!IsASCInitialized())
	{
		StealthCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::HandleASCInitialized);
		return;
	}
	
	EnsureAttributesAreReady();
}

void UStealthWidgetComponent::InitAbilitySystemData()
{
	StealthCharacter = Cast<AStealthBaseCharacter>(GetOwner());
	
	// Temp debug variables - remove later
	UAbilitySystemComponent* RawASC = StealthCharacter->GetAbilitySystemComponent();
	UAttributeSet* RawAS = StealthCharacter->GetAttributeSet();
	
	AttributeSet = Cast<UStealthAttributeSet>(RawAS);
	AbilitySystemComponent = Cast<UStealthAbilitySystemComponent>(RawASC);
}

bool UStealthWidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UStealthWidgetComponent::HandleASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UStealthAbilitySystemComponent>(ASC);
	AttributeSet = Cast<UStealthAttributeSet>(AS);
	
	if (!IsASCInitialized()) return; // just in case, but shouldn't get here ever
	EnsureAttributesAreReady();
	
}


void UStealthWidgetComponent::EnsureAttributesAreReady()
{
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddDynamic(this, &ThisClass::HandleAttributesInitialized);
	}
	else
	{
		HandleAttributesInitialized();
	}
}

void UStealthWidgetComponent::HandleAttributesInitialized()
{
	for (const auto& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair);
		
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

void UStealthWidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	USGAS_AttributeWidget* AttributeWidget = Cast<USGAS_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) return; // We only care about Attribute Widgets
	if (!AttributeWidget->MatchesAttributes(Pair)) return; // Only subscribe for matching Attributes

	
	// Update widget attribute values at beginning of game
	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get());

	// Update widget attribute values during game
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get());
	});
}

