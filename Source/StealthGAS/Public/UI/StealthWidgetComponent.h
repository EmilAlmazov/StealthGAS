// Copyright Emil Almazov

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "StealthWidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class STEALTHGAS_API UStealthWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:


protected:
	virtual void BeginPlay() override;
};
