// Copyright @MazenMorgan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilityTypes.generated.h"

class UMaterialInstance;
class UGameplayAbilityBase;

UENUM(BlueprintType)
enum class EAbilityCostType : uint8
{
	Health,
	Mana,
	Strength
};

USTRUCT(BlueprintType)
struct FGamePlayAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	float CooldownDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	float Cost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	UMaterialInstance* UIMat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	EAbilityCostType CostType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	TSubclassOf<UGameplayAbilityBase> AbilityClass;

	FGamePlayAbilityInfo();
	FGamePlayAbilityInfo(float InCooldownDuration, float InCost, UMaterialInstance* InUIMat, EAbilityCostType InCostType, TSubclassOf<UGameplayAbilityBase> InAbilityClass);
};