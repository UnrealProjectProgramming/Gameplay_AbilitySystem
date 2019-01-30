// Copyright @MazenMorgan

#include "GATargetActorGetAround.h"

#include "Abilities/GameplayAbility.h"

void AGATargetActorGetAround::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());

}

void AGATargetActorGetAround::ConfirmTargetingAndContinue()
{
	FVector ViewLocation;

	TArray<FOverlapResult> Overlaps;
	TArray<TWeakObjectPtr<AActor>> OverlappedActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;

	APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn)
	{
		QueryParams.AddIgnoredActor(MasterPawn);
		ViewLocation = MasterPawn->GetActorLocation();
	}

	bool bTryOverlap = GetWorld()->OverlapMultiByObjectType(Overlaps, ViewLocation,
		FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn),
		FCollisionShape::MakeSphere(SphereRadius), QueryParams);

	if (bTryOverlap)
	{
		for (int i = 0; i < Overlaps.Num(); ++i)
		{
			APawn* PawnOverlapped = Cast<APawn>(Overlaps[i].GetActor());
			if (PawnOverlapped)
			{
				OverlappedActors.AddUnique(PawnOverlapped);
			}
		}
	}

	if (OverlappedActors.Num() > 0)
	{
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlappedActors);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else
	{
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}
