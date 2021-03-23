// Fill out your copyright notice in the Description page of Project Settings.


#include "WavesPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AWavesPlayerController::BeginPlay() 
{
    Super::BeginPlay();
    HUD = CreateWidget(this, HUDClass);
    if(HUD) HUD->AddToViewport();
}

void AWavesPlayerController::GameHasEnded(class AActor *EndGameFocus, bool bIsWinner) 
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromViewport();
    if(bIsWinner)
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen) WinScreen->AddToViewport();
        UUserWidget* UpgradesScreen = CreateWidget(this, UpgradesScreenClass);
        if(UpgradesScreen) 
        {
            UpgradesScreen->AddToViewport();
            EnableCursor(true);
        }
    }
    else
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
        if(LoseScreen) LoseScreen->AddToViewport();
        GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
    }
}

void AWavesPlayerController::EnableCursor(bool bShowCursor) 
{
    bShowMouseCursor = bShowCursor;
    bEnableClickEvents = bShowCursor;
    bEnableMouseOverEvents = bShowCursor;
}