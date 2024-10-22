// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "ASCharacterBase.generated.h"

class UASAttributeSetBase;
class UGameplayAbilityBase;
struct FGameplayTag;

UCLASS()
class ABILIYSYSEM_API AASCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AASCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterBase")
	UAbilitySystemComponent* AbilitySystemComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "CharacterBase")
	UASAttributeSetBase* AttributeSetBaseComp;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void AquireAbility(TSubclassOf<class UGameplayAbility> AbilityToAquire);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void AquireAbilities(TArray<TSubclassOf<class UGameplayAbility>> AbilitiesToAquire);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "CharacterBase")
	bool IsOtherHostile(AASCharacterBase* Other);

	UFUNCTION()
	void OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnHealthChanged"))
	void BP_OnHealthChanged(float Health, float MaxHealth);

	UFUNCTION()
	void OnManaChanged(float Mana, float MaxMana);
	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnManaChanged"))
	void BP_OnManaChanged(float Mana, float MaxMana);

	UFUNCTION()
	void OnStrengthChanged(float Strength, float MaxStrength);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "OnStrengthChanged"))
	void BP_OnStrengthChanged(float Strength, float MaxStrength);

	UFUNCTION(BlueprintImplementableEvent, Category = "CharacterBase", meta = (DisplayName = "StartDyingSequence"))
	void BP_StartDyingSequence();

	void AutoDetermineTeamIDByControllerType();

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void AddGameplayTag(FGameplayTag &TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void RemoveGameplayTag(FGameplayTag &TagToRemove);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void PushCharacter(FVector ImpulseDirection, float ImpuseStrength, float StunDuration);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void Stun(float StunTime);

	UFUNCTION(BlueprintCallable, Category = "CharacterBase")
	void ApplyGESpecHandleToTargetDataSpecHandle(const FGameplayEffectSpecHandle& GESpecHandle, const FGameplayAbilityTargetDataHandle& TargetDataHandle);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag FullHealthTag;
	
protected:
	bool bHasDied;
	uint8 TeamID;
	FTimerHandle FrictionReenableDelay_TimeHandle;
	FTimerHandle Stun_TimeHandle;
	FTimerDelegate Stun_TimerDelegate;

	void Dead();
	void DisableInputControl();
	void EnableInputControl();
	void AddAbilityToUI(TSubclassOf<UGameplayAbilityBase> AbilityToAdd);

};
