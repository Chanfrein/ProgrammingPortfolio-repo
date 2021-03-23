// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
}

void AGun::ShotCooldown() 
{
	CanShoot = true;
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection) 
{

	AController* OwnerController = GetOwnerController();
	if(!OwnerController) return false;

	FVector Location;
	FRotator Rotation;
	FCollisionQueryParams Params;

	OwnerController->GetPlayerViewPoint(Location, Rotation);
	FVector End = Location + Rotation.Vector() * MaxRange;
	ShotDirection = -Rotation.Vector();
	
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn) return nullptr;

	return OwnerPawn->GetController();
}

void AGun::UpgradeDamage(float Amount) 
{
	Damage += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Upgraded sucessfully, damage is now %f"), Damage);
}

void AGun::UpgradeASpeed(float Amount) 
{
	AttackSpeed -= ((AttackSpeed/100.f) * Amount);
	UE_LOG(LogTemp, Warning, TEXT("Upgraded sucessfully, ASpeed is now %f"), AttackSpeed);
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger() 
{
	if(!CanShoot) return;

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	CanShoot = false;
	GetWorldTimerManager().SetTimer(FireRateTimer, this, &AGun::ShotCooldown, AttackSpeed, false);

	FHitResult Hit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(Hit, ShotDirection);
	if(bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Hit.Location);

		AActor* HitActor = Hit.GetActor();
		if(HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			AController *OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

