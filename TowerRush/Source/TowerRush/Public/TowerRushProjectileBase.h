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

    /** Ÿ�� ���� (���� �̻��� ����) */
    void SetHomingTarget(AActor* Target);

protected:
    /** �浹 ó�� */
    UPROPERTY(EditAnywhere, Category = "Components")
    class USphereComponent* CollisionComponent;

    /** �޽� (����ü ������) */
    UPROPERTY(EditAnywhere, Category = "Components")
    class UStaticMeshComponent* MeshComponent;

    /** ����ü �̵� */
    UPROPERTY(EditAnywhere, Category = "Components")
    class UProjectileMovementComponent* ProjectileMovement;

    /** ���� ����Ʈ */
    UPROPERTY(EditAnywhere, Category = "Effects")
    class UParticleSystem* ExplosionEffect;

    /** ���� �̻��� ���� */
    UPROPERTY(EditAnywhere, Category = "Homing")
    bool bIsHoming = false;

    /** ���� ���� �ݰ� */
    UPROPERTY(EditAnywhere, Category = "Explosion")
    float ExplosionRadius = 200.0f;

    /** �⺻ ������ */
    UPROPERTY(EditAnywhere, Category = "Damage")
    float Damage = 50.0f;

    /** ���� �̻��� Ÿ�� */
    UPROPERTY(EditAnywhere, Category = "Homing")
    AActor* HomingTarget;

    /** ����ü �ӵ� ���� */
    UPROPERTY(EditAnywhere, Category = "Movement")
    float ProjectileSpeed = 2000.0f;
};
