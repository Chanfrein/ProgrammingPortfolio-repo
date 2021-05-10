// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UBehaviorTree;

UCLASS()
class GROW_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;	
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	//REFERENCES
	UPROPERTY(VisibleAnywhere)
	APawn* PlayerPawn;

	//COMPONENTS
	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	void SetBlackboardSelfPosition();
};
