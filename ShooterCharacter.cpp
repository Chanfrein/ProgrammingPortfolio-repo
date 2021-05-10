// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Actors/Gun.h"
#include "Components/CapsuleComponent.h"
#include "GrowGameModeBase.h"
#include "UpgradesGameInstance.h"
#include "Kismet/GameplayStatics.h"

AShooterCharacter::AShooterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	
	UUpgradesGameInstance* GameInstance = Cast<UUpgradesGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if(GameInstance) GameInstance->ApplyUpgrades(this);

	Health = MaxHealth;
}

void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &AShooterCharacter::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookSide"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;

	if(IsDead())
	{
		AGrowGameModeBase* GameMode = GetWorld()->GetAuthGameMode<AGrowGameModeBase>();
		if(GameMode)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	return DamageApplied;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealthPerent() const
{
	return Health / MaxHealth;
}

void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterCharacter::MoveForward(float AxisValue) 
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveSide(float AxisValue) 
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::UpgradeWeaponDamage(float Amount) 
{
	Gun->UpgradeDamage(Amount);
}

void AShooterCharacter::UpgradeWeaponASpeed(float Amount) 
{
	Gun->UpgradeASpeed(Amount);
}

void AShooterCharacter::UpgradeHealth(float Amount) 
{
	MaxHealth += Amount;
}

void AShooterCharacter::Shoot() 
{
	Gun->PullTrigger();
}