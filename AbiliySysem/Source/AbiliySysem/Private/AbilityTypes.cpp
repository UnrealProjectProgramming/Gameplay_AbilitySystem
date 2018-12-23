// Copyright @MazenMorgan

#include "AbilityTypes.h"

FGamePlayAbilityInfo::FGamePlayAbilityInfo()
	:CooldownDuration(0),
	Cost(0),
	UIMat(nullptr),
	CostType(EAbilityCostType::Mana),
	AbilityClass(nullptr)
{

}

FGamePlayAbilityInfo::FGamePlayAbilityInfo(float InCooldownDuration, float InCost, UMaterialInstance* InUIMat, EAbilityCostType InCostType, TSubclassOf<UGameplayAbilityBase> InAbilityClass)
	:CooldownDuration(InCooldownDuration),
	Cost(InCost),
	UIMat(InUIMat),
	CostType(InCostType),
	AbilityClass(InAbilityClass)
{

}
