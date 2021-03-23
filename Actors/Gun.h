// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class GROW_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();

	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	UFUNCTION()
	void UpgradeDamage(float Amount);
	UFUNCTION()
	void UpgradeASpeed(float Amount);

protected:
	virtual void BeginPlay() override;

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitFlash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	USoundBase* MuzzleSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	USoundBase* HitSound;

	//FUNCTIONS
	void ShotCooldown();
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	//VARIABLES
	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxRange = 1500.f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float Damage = 10.f;
	UPROPERTY(EditAnywhere, Category = "Stats")
	float AttackSpeed = 0.5f;
	UPROPERTY(VisibleAnywhere)
	bool CanShoot = true;

	FTimerHandle FireRateTimer;

	//REFERENCES
	AController* GetOwnerController() const;


};
