// Copyright @MazenMorgan

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorGroundSelect.generated.h"

class UGameplayAbility;
class UDecalComponent;
class USceneComponent;
/**
 * 
 */
UCLASS()
class ABILIYSYSEM_API AGATargetActorGroundSelect : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	AGATargetActorGroundSelect();
	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "GroundSelect")
	bool GetPlayerLookingPoint(FVector& OutViewPoint);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true),Category = "GroundSelect")
	float SphereRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GroundSelect")
	UDecalComponent* DecalComp;

	USceneComponent* SceneComp;
};
