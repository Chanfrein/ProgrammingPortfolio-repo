// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class UGameInstance;

UCLASS()
class GROW_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:	
	AShooterCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	void Shoot();

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealthPerent() const;

	UFUNCTION()
	void UpgradeWeaponDamage(float Amount);
	UFUNCTION()
	void UpgradeWeaponASpeed(float Amount);	
	UFUNCTION()
	void UpgradeHealth(float Amount);

protected:
	virtual void BeginPlay() override;

private:
	//FUNCTIONS
	void MoveForward(float AxisValue);
	void MoveSide(float AxisValue);

	//COMPONENTS
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AGun> GunClass;
	UPROPERTY(EditAnywhere)
	AGun* Gun;

	//VARIABLES
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	float Health;
};
