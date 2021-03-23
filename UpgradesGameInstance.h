// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UpgradesGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GROW_API UUpgradesGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void AddDamageUpgrade(float amount);
	void AddASpeedUpgrade(float amount);
	void AddHealthUpgrade(float amount);

	UFUNCTION()
	void ApplyUpgrades(AShooterCharacter* CharacterToUpgrade);

private:
	UPROPERTY(VisibleAnywhere)
	TArray<float> DamageUpgrades;
	UPROPERTY(VisibleAnywhere)
	TArray<float> ASpeedUpgrades;
	UPROPERTY(VisibleAnywhere)
	TArray<float> HealthUpgrades;
};
