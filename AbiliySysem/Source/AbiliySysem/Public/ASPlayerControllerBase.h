// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AbilityTypes.h"
#include "ASPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class ABILIYSYSEM_API AASPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerControllerBase")
	void AddAbilityToUI(FGamePlayAbilityInfo AbilityInfo);
};
