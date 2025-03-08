#include "TowerRushProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ATowerRushProjectileBase::ATowerRushProjectileBase()
{
    PrimaryActorTick.bCanEverTick = true;

    // 충돌 컴포넌트
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(10.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
    RootComponent = CollisionComponent;

    // 메쉬 컴포넌트 (디자인 추가)
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    // 투사체 이동
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = ProjectileSpeed;
    ProjectileMovement->MaxSpeed = ProjectileSpeed * 1.5f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    // 충돌 이벤트 바인딩
    CollisionComponent->OnComponentHit.AddDynamic(this, &ATowerRushProjectileBase::OnHit);
}

void ATowerRushProjectileBase::BeginPlay()
{
    Super::BeginPlay();

    // 초기 속도 설정
    if (ProjectileMovement)
    {
        ProjectileMovement->InitialSpeed = ProjectileSpeed;
        ProjectileMovement->MaxSpeed = ProjectileSpeed * 1.5f;
    }
}

void ATowerRushProjectileBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 유도 미사일 기능
    if (bIsHoming && HomingTarget)
    {
        ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
        ProjectileMovement->bIsHomingProjectile = true;
        ProjectileMovement->HomingAccelerationMagnitude = 5000.0f;
    }
}

/** 유도 타겟 설정 */
void ATowerRushProjectileBase::SetHomingTarget(AActor* Target)
{
    if (Target)
    {
        HomingTarget = Target;
        bIsHoming = true;
    }
}

/** 충돌 처리 */
void ATowerRushProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // 폭발 효과 실행
    if (ExplosionEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
    }

    // 폭발 반경 내 피해 적용
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

    // 어떤 오브젝트에든 부딪히면 사라짐
    Destroy();
}
