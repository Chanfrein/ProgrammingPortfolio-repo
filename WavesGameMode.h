// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrowGameModeBase.h"
#include "WavesGameMode.generated.h"

class AShooterCharacter;

UCLASS()
class GROW_API AWavesGameMode : public AGrowGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

	UFUNCTION()
	void SetupEnemies();


protected:
	virtual void BeginPlay() override;

private:
	void EndGame(bool bIsPlayerWinner);

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AShooterCharacter> EnemyClass;
};
