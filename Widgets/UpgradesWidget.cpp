// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradesWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Grow/ShooterCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "../WavesPlayerController.h"
#include "../UpgradesGameInstance.h"


void UUpgradesWidget::NativeConstruct() 
{
    Super::NativeConstruct();

    DamageUpgradeButton->OnClicked.AddUniqueDynamic(this, &UUpgradesWidget::OnDamageClicked);
    ASpeedUpgradeButton->OnClicked.AddUniqueDynamic(this, &UUpgradesWidget::OnASpeedClicked);
    HealthUpgradeButton->OnClicked.AddUniqueDynamic(this, &UUpgradesWidget::OnHealthClicked);

    PlayerCharacter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    Controller = Cast<AWavesPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
    GameInstance = Cast<UUpgradesGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    DamageUpgradeAmount = FMath::RandRange(2, 5);
	ASpeedUpgradeAmount = FMath::RandRange(8, 12);
	HealthUpgradeAmount = FMath::RandRange(10, 20);

    DamageUpgradeLabel->SetText(FText::Format(FText::FromString(TEXT("+{0} Weapon Damage")), FText::AsNumber(DamageUpgradeAmount)));
    ASpeedUpgradeLabel->SetText(FText::Format(FText::FromString(TEXT("+{0}% Attack Speed")), FText::AsNumber(ASpeedUpgradeAmount)));
    HealthUpgradeLabel->SetText(FText::Format(FText::FromString(TEXT("+{0} Maximum Health")), FText::AsNumber(HealthUpgradeAmount)));
}

void UUpgradesWidget::OnDamageClicked() 
{
    if(PlayerCharacter)
    {
        PlayerCharacter->UpgradeWeaponDamage(DamageUpgradeAmount);
        if(GameInstance) GameInstance->AddDamageUpgrade(DamageUpgradeAmount);
        if(Controller) Controller->RestartLevel();
    } 
}

void UUpgradesWidget::OnASpeedClicked() 
{
    if(PlayerCharacter)
    {
        PlayerCharacter->UpgradeWeaponASpeed(ASpeedUpgradeAmount);
        if(GameInstance) GameInstance->AddASpeedUpgrade(ASpeedUpgradeAmount);
        if(Controller) Controller->RestartLevel();
    }
}

void UUpgradesWidget::OnHealthClicked() 
{
    if(PlayerCharacter)
    {
        PlayerCharacter->UpgradeHealth(HealthUpgradeAmount);
        if(GameInstance) GameInstance->AddHealthUpgrade(HealthUpgradeAmount);
        if(Controller) Controller->RestartLevel();
    }
}