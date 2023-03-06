// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"

#include "Kismet/GameplayStatics.h"


AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(Root);
}


void AGun::BeginPlay()
{
	Super::BeginPlay();
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	if (GetOwnerController() == nullptr)return false;
	FVector Location;
	FRotator Rotation;
	GetOwnerController()->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	FVector End = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	const APawn* PawnOwner = Cast<APawn>(GetOwner());
	if (PawnOwner == nullptr)return nullptr;
	return PawnOwner->GetController();
}


void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticle, GunMesh,TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh,TEXT("MuzzleFlashSocket"));

	FHitResult HitResult;
	FVector ShotDirection;
	if (GunTrace(HitResult, ShotDirection))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, HitResult.Location,
		                                         ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.Location);


		AActor* HitActor = HitResult.GetActor();
		if (HitActor == nullptr)return;
		FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
		HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
	}
}
