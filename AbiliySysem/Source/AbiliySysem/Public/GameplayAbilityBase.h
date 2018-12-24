// Copyright @MazenMorgan

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "AbilityTypes.h"


#include "GameplayAbilityBase.generated.h"

class UMaterialInstance;

/**
 * 
 */
UCLASS()
class ABILIYSYSEM_API UGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityBase")
	UMaterialInstance* UIMaterial;

	UFUNCTION(BlueprintCallable, Category = "AbilityBase")
	FGamePlayAbilityInfo AbilityInfo();
	
};
