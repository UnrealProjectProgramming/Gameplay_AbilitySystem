// Copyright @MazenMorgan

#include "DamageExecutionCalculation.h"
#include "ASAttributeSetBase.h"

// Helper macros for declaring attribute captures, Check GameplayEffectExecutionCalculation.h 
struct DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)

	DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UASAttributeSetBase, AttackDamage, Source, true)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UASAttributeSetBase, Armor, Target, true)
	}

};

static DamageStatics& GetDamageStatics()
{
	static DamageStatics DamageStaticsVar;
	return DamageStaticsVar;
}

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	//  We can do this in the DamageStatics using DELCARE AND DEFINE MACROS !
	HealthProperty = FindFieldChecked<UProperty>(UASAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UASAttributeSetBase, Health));
	HealthDef = FGameplayEffectAttributeCaptureDefinition(HealthProperty, EGameplayEffectAttributeCaptureSource::Target, true);

	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().AttackDamageDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().ArmorDef);
}

void UDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// we can get the ability Target component and the source as well , and from them we can get the owning actor and do the stuff we want !
	float AttackDamageMagnitude = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().AttackDamageDef, FAggregatorEvaluateParameters(), AttackDamageMagnitude);
	float ArmorMagnitude = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().ArmorDef, FAggregatorEvaluateParameters(), ArmorMagnitude);

	// We captured both Attach and Armor Magnitutes and here below you can do whatever calculations you want ! 
	float FinalDamage = FMath::Clamp(AttackDamageMagnitude - ArmorMagnitude, 0.0f, AttackDamageMagnitude - ArmorMagnitude);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty, EGameplayModOp::Additive, -FinalDamage));
}

