// Fill out your copyright notice in the Description page of Project Settings.

// This like mana health stamina ... anything that I wanna have in my game mechanics but we have to have this partical class so 
//the game play effect acutally can tweak these numbers.


#include "ASAttributeSetBase.h"

#include "GameplayAbilities/Public/GameplayEffectExtension.h"
#include "UnrealType.h"
#include "Misc/AssertionMacros.h"
#include "GameplayEffect.h"

UASAttributeSetBase::UASAttributeSetBase() : Health(200), MaxHealth(200)
{
	
}

// Executes after the gameplay effect blueprint
void UASAttributeSetBase::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
	// first Line in the if condition is to get the Attribute that got modified by any game play effect
	// then we check whether this attribute is the same attribute we wanna check against which is health
	if(Data.EvaluatedData.Attribute.GetUProperty() == 
		FindFieldChecked<UProperty>(UASAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UASAttributeSetBase, Health)))
	{
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue()));
		Health.SetBaseValue(FMath::Clamp(Health.GetBaseValue(), 0.0f, MaxHealth.GetCurrentValue()));
		UE_LOG(LogTemp, Warning, TEXT("Ouch, I took some damager, now my HP is : %f"), Health.GetCurrentValue());
		// We are trying to create and delegate and we broadcast it when out health Change so the character can subscribe to it.
		OnHealthChange.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}
}
