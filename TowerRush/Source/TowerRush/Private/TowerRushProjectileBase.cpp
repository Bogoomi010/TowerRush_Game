#include "TowerRushProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ATowerRushProjectileBase::ATowerRushProjectileBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // �浹 ������Ʈ
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(10.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
    RootComponent = CollisionComponent;

    // �޽� ������Ʈ (������ �߰�)
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // ����ü �̵�
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = ProjectileSpeed;
    ProjectileMovement->MaxSpeed = ProjectileSpeed * 1.5f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    // �浹 �̺�Ʈ ���ε�
    CollisionComponent->OnComponentHit.AddDynamic(this, &ATowerRushProjectileBase::OnHit);
}

void ATowerRushProjectileBase::BeginPlay()
{
    Super::BeginPlay();

    // �ʱ� �ӵ� ����
    if (ProjectileMovement)
    {
        ProjectileMovement->InitialSpeed = ProjectileSpeed;
        ProjectileMovement->MaxSpeed = ProjectileSpeed * 1.5f;
    }
}

void ATowerRushProjectileBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ���� �̻��� ���
    if (bIsHoming && HomingTarget)
    {
        ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
        ProjectileMovement->bIsHomingProjectile = true;
        ProjectileMovement->HomingAccelerationMagnitude = 5000.0f;
    }
}

/** ���� Ÿ�� ���� */
void ATowerRushProjectileBase::SetHomingTarget(AActor* Target)
{
    if (Target)
    {
        HomingTarget = Target;
        bIsHoming = true;
    }
}

/** �浹 ó�� */
void ATowerRushProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // ���� ȿ�� ����
    if (ExplosionEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
    }

    // ���� �ݰ� �� ���� ����
    TArray<AActor*> OverlappedActors;
    UGameplayStatics::ApplyRadialDamage(
        this,
        Damage,
        GetActorLocation(),
        ExplosionRadius,
        UDamageType::StaticClass(),
        OverlappedActors,
        this,
        GetInstigatorController(),
        true
    );

    // � ������Ʈ���� �ε����� �����
    Destroy();
}
