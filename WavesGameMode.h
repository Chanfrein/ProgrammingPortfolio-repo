// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GrowGameModeBase.h"
#include "WavesGameMode.generated.h"


UCLASS()
class GROW_API AWavesGameMode : public AGrowGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void EndGame(bool bIsPlayerWinner);
};
