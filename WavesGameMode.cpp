// Fill out your copyright notice in the Description page of Project Settings.


#include "WavesGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UpgradesGameInstance.h"

void AWavesGameMode::BeginPlay() 
{
    Super::BeginPlay();

    FTimerHandle TimerHandle;
    float TimerDelay = 2.f;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &AWavesGameMode::SetupEnemies, TimerDelay, false);
}

void AWavesGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if(PlayerController)
    {
        EndGame(false);
    }

    for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!Controller->IsDead())
        {
            return;
        }
    }

    EndGame(true);
}

void AWavesGameMode::SetupEnemies() 
{
    FVector StartingLocation = FVector(-6900, 2000, 100);
    FRotator StartingRotation = FRotator(0,0,0);
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
    UUpgradesGameInstance* GameInstance = Cast<UUpgradesGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    UE_LOG(LogTemp, Warning, TEXT("Checking for GameInstance and EnemyClass nulls"));
    if(!GameInstance || !EnemyClass) return;

    int32 WaveCount = GameInstance->GetWaveCount();

    UE_LOG(LogTemp, Warning, TEXT("No nulls, starting for loop with wavecount of %i"), WaveCount);

    for(int32 i = 1; i <= WaveCount; i++)
    {
        AShooterCharacter* EnemyAI = GetWorld()->SpawnActor<AShooterCharacter>(EnemyClass, StartingLocation, StartingRotation, SpawnParams);
        StartingLocation.Set(-6900, 2000-(500*i), 100);
        UE_LOG(LogTemp, Warning, TEXT("Added one enemy"));
    }

}

void AWavesGameMode::EndGame(bool bIsPlayerWinner) 
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}


