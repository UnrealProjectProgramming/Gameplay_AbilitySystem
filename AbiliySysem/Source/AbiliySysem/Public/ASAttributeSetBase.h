// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "ASAttributeSetBase.generated.h"

/**
 * 
 */
UCLASS()
class ABILIYSYSEM_API UASAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()

public:
	UASAttributeSetBase();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeSetBase")
	FGameplayAttributeData Health;
	
};
