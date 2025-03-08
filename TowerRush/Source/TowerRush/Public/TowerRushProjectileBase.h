#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerRushProjectileBase.generated.h"

UCLASS()
class TOWERRUSH_API ATowerRushProjectileBase : public AActor
{
    GENERATED_BODY()

public:
    ATowerRushProjectileBase();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    /** 타겟 설정 (유도 미사일 전용) */
    void SetHomingTarget(AActor* Target);

protected:
    /** 충돌 처리 */
    UPROPERTY(EditAnywhere, Category = "Components")
    class USphereComponent* CollisionComponent;

    /** 메쉬 (투사체 디자인) */
    UPROPERTY(EditAnywhere, Category = "Components")
    class UStaticMeshComponent* MeshComponent;

    /** 투사체 이동 */
    UPROPERTY(EditAnywhere, Category = "Components")
    class UProjectileMovementComponent* ProjectileMovement;

    /** 폭발 이펙트 */
    UPROPERTY(EditAnywhere, Category = "Effects")
    class UParticleSystem* ExplosionEffect;

    /** 유도 미사일 여부 */
    UPROPERTY(EditAnywhere, Category = "Homing")
    bool bIsHoming = false;

    /** 폭발 피해 반경 */
    UPROPERTY(EditAnywhere, Category = "Explosion")
    float ExplosionRadius = 200.0f;

    /** 기본 데미지 */
    UPROPERTY(EditAnywhere, Category = "Damage")
    float Damage = 50.0f;

    /** 유도 미사일 타겟 */
    UPROPERTY(EditAnywhere, Category = "Homing")
    AActor* HomingTarget;

    /** 투사체 속도 조절 */
    UPROPERTY(EditAnywhere, Category = "Movement")
    float ProjectileSpeed = 2000.0f;
};
