// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UpgradesWidget.generated.h"

class UButton;
class UTextBlock;
class AShooterCharacter;
class AWavesPlayerController;
class UUpgradesGameInstance;

UCLASS()
class GROW_API UUpgradesWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	//COMPONENTS
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* DamageUpgradeLabel;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ASpeedUpgradeLabel;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* HealthUpgradeLabel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* DamageUpgradeButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ASpeedUpgradeButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* HealthUpgradeButton;

	//FUNCTIONS
	UFUNCTION()
	void OnDamageClicked();
	UFUNCTION()
	void OnASpeedClicked();
	UFUNCTION()
	void OnHealthClicked();

	void NativeConstruct() override;

private:
	//VARIABLES
	UPROPERTY(VisibleAnywhere)
	float DamageUpgradeAmount;
	UPROPERTY(VisibleAnywhere)
	float ASpeedUpgradeAmount;
	UPROPERTY(VisibleAnywhere)
	float HealthUpgradeAmount;

	//REFERENCES
	UPROPERTY(VisibleAnywhere)
	UUpgradesGameInstance* GameInstance;
	UPROPERTY(VisibleAnywhere)
	AWavesPlayerController* Controller;
	UPROPERTY(VisibleAnywhere)
	AShooterCharacter* PlayerCharacter;
};
