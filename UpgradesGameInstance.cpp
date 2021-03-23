// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradesGameInstance.h"
#include "ShooterCharacter.h"

void UUpgradesGameInstance::AddDamageUpgrade(float amount) 
{
    DamageUpgrades.Add(amount);
}

void UUpgradesGameInstance::AddASpeedUpgrade(float amount) 
{
    ASpeedUpgrades.Add(amount);
}

void UUpgradesGameInstance::AddHealthUpgrade(float amount) 
{
    HealthUpgrades.Add(amount);
}

void UUpgradesGameInstance::ApplyUpgrades(AShooterCharacter* CharacterToUpgrade) 
{
    if(!CharacterToUpgrade || !CharacterToUpgrade->IsPlayerControlled()) return;

    for(float value : DamageUpgrades)
    {
       CharacterToUpgrade->UpgradeWeaponDamage(value);
    }

    for(float value : ASpeedUpgrades)
    {
        CharacterToUpgrade->UpgradeWeaponASpeed(value);
    }

    for(float value : HealthUpgrades)
    {
        CharacterToUpgrade->UpgradeHealth(value);
    }
}
