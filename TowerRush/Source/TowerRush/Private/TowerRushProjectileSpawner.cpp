#include "TowerRushProjectileSpawner.h"
#include "TowerRushProjectileBase.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

ATowerRushProjectileSpawner::ATowerRushProjectileSpawner()
{
    PrimaryActorTick.bCanEverTick = false;

    DetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectionSphere"));
    if (DetectionSphere)
    {
        DetectionSphere->InitSphereRadius(500.0f);
        DetectionSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
        DetectionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        DetectionSphere->SetCollisionResponseToAllChannels(ECR_Overlap);
        RootComponent = DetectionSphere;

        DetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &ATowerRushProjectileSpawner::OnTargetDetected);
        DetectionSphere->OnComponentEndOverlap.AddDynamic(this, &ATowerRushProjectileSpawner::OnTargetLost);
    }
}

void ATowerRushProjectileSpawner::BeginPlay()
{
    Super::BeginPlay();
    if (!ProjectileClass)
    {
        UE_LOG(LogTemp, Error, TEXT("ProjectileClass is not set in %s. Spawning disabled."), *GetName());
        return;
    }
}

void ATowerRushProjectileSpawner::OnTargetDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && (OtherActor->ActorHasTag("Player") || OtherActor->ActorHasTag("Creep")))
    {
        TargetActor = OtherActor;
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Target Entered: %s"), *OtherActor->GetName()));
        UE_LOG(LogTemp, Warning, TEXT("Target Entered: %s"), *OtherActor->GetName());

        if (!GetWorld()->GetTimerManager().IsTimerActive(SpawnTimerHandle))
        {
            GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ATowerRushProjectileSpawner::SpawnProjectile, SpawnInterval, true);
        }
    }
}

void ATowerRushProjectileSpawner::OnTargetLost(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor == TargetActor)
    {
        GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Target Lost: %s"), *OtherActor->GetName()));
        UE_LOG(LogTemp, Warning, TEXT("Target Lost: %s"), *OtherActor->GetName());

        TargetActor = nullptr;
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
    }
}



void ATowerRushProjectileSpawner::SpawnProjectile()
{
    if (!ProjectileClass || !TargetActor)
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }

    FVector SpawnLocation = GetActorLocation() + (GetActorForwardVector() * 100.0f);
    FRotator SpawnRotation = (TargetActor->GetActorLocation() - GetActorLocation()).Rotation();

    ATowerRushProjectileBase* SpawnedProjectile = GetWorld()->SpawnActor<ATowerRushProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
    if (SpawnedProjectile)
    {
        SpawnedProjectile->SetHomingTarget(TargetActor);
        UE_LOG(LogTemp, Warning, TEXT("Projectile Spawned at %s targeting %s"), *SpawnLocation.ToString(), *TargetActor->GetName());
    }
}
