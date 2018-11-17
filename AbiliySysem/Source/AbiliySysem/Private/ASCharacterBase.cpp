// Fill out your copyright notice in the Description page of Project Settings.

#include "ASCharacterBase.h"

// Sets default values
AASCharacterBase::AASCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
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

