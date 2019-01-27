// Copyright @MazenMorgan

#include "GATargetActorGroundSelect.h"


#include "Abilities/GameplayAbility.h"

void AGATargetActorGroundSelect::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGATargetActorGroundSelect::ConfirmTargetingAndContinue()
{
	FVector ViewPoint;
	FRotator ViewRotation;
	if (MasterPC)
	{
		MasterPC->GetActorEyesViewPoint(ViewPoint, ViewRotation);
	}

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	APawn* MasterPawn = MasterPC->GetPawn();

	if (MasterPawn)
	{
		QueryParams.AddIgnoredActor(MasterPawn); // Or WE can use MasterPawn->GetUniqueID
	}

	FVector LookAtPoint = FVector();
	bool TryLineTrace = GetWorld()->LineTraceSingleByChannel(HitResult, ViewPoint, ViewPoint + ViewRotation.Vector() * 10000.0f, ECC_Visibility, QueryParams);

	if (TryLineTrace)
	{
		LookAtPoint = HitResult.ImpactPoint;
	}
}
