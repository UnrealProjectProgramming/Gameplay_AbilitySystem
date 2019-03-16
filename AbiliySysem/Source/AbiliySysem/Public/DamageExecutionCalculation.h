// Copyright @MazenMorgan

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class ABILIYSYSEM_API UDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

	UDamageExecutionCalculation();
	UProperty* HealthProperty;
	FGameplayEffectAttributeCaptureDefinition HealthDef;

public:
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
