#include "TowerRushProjectileSpawner.h"
#include "TowerRushProjectileBase.h"
#include "Engine/World.h"
#include "TimerManager.h"

ATowerRushProjectileSpawner::ATowerRushProjectileSpawner()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATowerRushProjectileSpawner::BeginPlay()
{
    Super::BeginPlay();

    if (!ProjectileClass)
    {
        UE_LOG(LogTemp, Error, TEXT("ProjectileClass is not set in %s. Spawning disabled."), *GetName());
        return;
    }

    // 일정 간격마다 투사체 생성
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ATowerRushProjectileSpawner::SpawnProjectile, SpawnInterval, true);
}

void ATowerRushProjectileSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATowerRushProjectileSpawner::SpawnProjectile()
{
    if (!ProjectileClass)
    {
        UE_LOG(LogTemp, Error, TEXT("ProjectileClass is not set in %s"), *GetName());
        return;
    }

    FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 100.0f);
    FRotator SpawnRotation = GetActorRotation();

    ATowerRushProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<ATowerRushProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
    if (SpawnedProjectile)
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile Spawned: %s"), *SpawnedProjectile->GetName());
    }
}
