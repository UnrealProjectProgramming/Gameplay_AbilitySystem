// Fill out your copyright notice in the Description page of Project Settings.

#include "ASCharacterBase.h"

#include "Abilities/GameplayAbility.h"
#include "ASAttributeSetBase.h"
#include "AIController.h"
#include "GameFramework/PlayerController.h"
#include "BrainComponent.h"

// Sets default values
AASCharacterBase::AASCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AttributeSetBaseComp = CreateDefaultSubobject<UASAttributeSetBase>(TEXT("AttributeSetBaseComp"));
	bHasDied = false;
	TeamID = 255;
}

// Called when the game starts or when spawned
void AASCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// Subscribing to OnHealthChangedDelegate
	if (AttributeSetBaseComp)
	{
		AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &AASCharacterBase::OnHealthChanged);
		AttributeSetBaseComp->OnManaChange.AddDynamic(this, &AASCharacterBase::OnManaChanged);
		AttributeSetBaseComp->OnStrengthChange.AddDynamic(this, &AASCharacterBase::OnStrengthChanged);
	}
	AutoDetermineTeamIDByControllerType();
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

bool AASCharacterBase::IsOtherHostile(AASCharacterBase* Other)
{
	return TeamID != Other->TeamID;
}

void AASCharacterBase::OnHealthChanged(float Health, float MaxHealth)
{
	if (Health <= 0 && !bHasDied)
	{
		bHasDied = true;
		Dead();
		BP_StartDyingSequence();
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

void AASCharacterBase::OnManaChanged(float Mana, float MaxMana)
{
	BP_OnManaChanged(Mana, MaxMana);
}

void AASCharacterBase::OnStrengthChanged(float Strength, float MaxStrength)
{
	BP_OnStrengthChanged(Strength, MaxStrength);
}

void AASCharacterBase::AutoDetermineTeamIDByControllerType()
{
	if (GetController() && GetController()->IsPlayerController())
	{
		TeamID = 0;
	}
}

void AASCharacterBase::Dead()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->DisableInput(PC);
	}
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Dead");
	}
}

