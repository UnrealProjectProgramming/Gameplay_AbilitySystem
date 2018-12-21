// Fill out your copyright notice in the Description page of Project Settings.

// This like mana health stamina ... anything that I wanna have in my game mechanics but we have to have this partical class so 
//the game play effect acutally can tweak these numbers.


#include "ASAttributeSetBase.h"

#include "GameplayAbilities/Public/GameplayEffectExtension.h"
#include "UnrealType.h"
#include "Misc/AssertionMacros.h"
#include "GameplayEffect.h"
#include "ASCharacterBase.h"

UASAttributeSetBase::UASAttributeSetBase() : Health(200), MaxHealth(200), Mana(150.0f), MaxMana(150.0f), Strength(250.0f), MaxStrength(250.0f)
{
	
}

// Executes after the gameplay effect blueprint
void UASAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	// first Line in the if condition is to get the Attribute that got modified by any game play effect
	// then we check whether this attribute is the same attribute we wanna check against which is health
	if (Data.EvaluatedData.Attribute.GetUProperty() ==
		FindFieldChecked<UProperty>(UASAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UASAttributeSetBase, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetCurrentValue()));
		// We are trying to create and delegate and we broadcast it when our health Change so the character can subscribe to it.
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());

		AASCharacterBase* CharacterOwner = Cast<AASCharacterBase>(GetOwningActor());
		if (Health.GetCurrentValue() == MaxHealth.GetCurrentValue())
		{
			if (CharacterOwner)
			{
				CharacterOwner->AddGameplayTag(CharacterOwner->FullHealthTag);
			}
		}
		else
		{
			if (CharacterOwner)
			{
				CharacterOwner->RemoveGameplayTag(CharacterOwner->FullHealthTag);
			}
		}
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() ==
		FindFieldChecked<UProperty>(UASAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UASAttributeSetBase, Mana)))
	{
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.0f, MaxMana.GetCurrentValue()));
		Mana.SetBaseValue(FMath::Clamp(Mana.GetBaseValue(), 0.0f, MaxMana.GetCurrentValue()));
		// We are trying to create and delegate and we broadcast it when out health Change so the character can subscribe to it.
		OnManaChange.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}

	if (Data.EvaluatedData.Attribute.GetUProperty() ==
		FindFieldChecked<UProperty>(UASAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UASAttributeSetBase, Strength)))
	{
		Strength.SetCurrentValue(FMath::Clamp(Strength.GetCurrentValue(), 0.0f, MaxStrength.GetCurrentValue()));
		Strength.SetBaseValue(FMath::Clamp(Strength.GetBaseValue(), 0.0f, MaxStrength.GetCurrentValue()));
		// We are trying to create and delegate and we broadcast it when out health Change so the character can subscribe to it.
		OnStrengthChange.Broadcast(Strength.GetCurrentValue(), MaxStrength.GetCurrentValue());
	}
}

