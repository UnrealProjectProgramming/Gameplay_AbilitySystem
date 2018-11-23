// Fill out your copyright notice in the Description page of Project Settings.

#include "ASCharacterBase.h"

#include "Abilities/GameplayAbility.h"
#include "ASAttributeSetBase.h"

// Sets default values
AASCharacterBase::AASCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AttributeSetBaseComp = CreateDefaultSubobject<UASAttributeSetBase>(TEXT("AttributeSetBaseComp"));
	bHasDied = false;
}

// Called when the game starts or when spawned
void AASCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Subscribing to OnHealthChangedDelegate
	if (AttributeSetBaseComp)
	{
		AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &AASCharacterBase::OnHealthChanged);
	}
	
}

// Called every frame
void AASCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AASCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AASCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}

void AASCharacterBase::AquireAbility(TSubclassOf<UGameplayAbility> AbilityToAquire)
{
	if (AbilitySystemComp)
	{
		if (HasAuthority() && AbilityToAquire)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAquire, 1, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

void AASCharacterBase::OnHealthChanged(float Health, float MaxHealth)
{
	if (Health <= 0 && !bHasDied)
	{
		BP_StartDyingSequence();
		bHasDied = true;
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

