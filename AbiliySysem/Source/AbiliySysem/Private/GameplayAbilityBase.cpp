// Copyright @MazenMorgan

#include "GameplayAbilityBase.h"

FGamePlayAbilityInfo UGameplayAbilityBase::AbilityInfo()
{
	UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();
	
	if (CooldownEffect && CostEffect)
	{
		float CooldownDuration = 0;
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration);
		float Cost = 0;
		EAbilityCostType CostType;
		if (CostEffect->Modifiers.Num() > 0)
		{
			FGameplayModifierInfo ModifierInfo = CostEffect->Modifiers[0];
			ModifierInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
			FString AbilityName = ModifierInfo.Attribute.AttributeName;
			if (AbilityName == "Health")
			{
				CostType = EAbilityCostType::Health;
			}
			else if (AbilityName == "Mana")
			{
				CostType = EAbilityCostType::Mana;
			}
			else if (AbilityName == "Strength")
			{
				CostType = EAbilityCostType::Strength;
			}
			return FGamePlayAbilityInfo(CooldownDuration, Cost, UIMaterial, CostType, GetClass());
		}
	}
	return FGamePlayAbilityInfo();
}
