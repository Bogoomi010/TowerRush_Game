#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerRushProjectileSpawner.generated.h"

UCLASS()
class TOWERRUSH_API ATowerRushProjectileSpawner : public AActor
{
    GENERATED_BODY()

public:
    ATowerRushProjectileSpawner();

protected:
    virtual void BeginPlay() override;

    /** ���� ���ݸ��� ����ü ���� */
    void SpawnProjectile();

    /** Ÿ�̸� �ڵ� */
    FTimerHandle SpawnTimerHandle;

    /** ���� ���� */
    UPROPERTY(VisibleAnywhere, Category = "Detection")
    class USphereComponent* DetectionSphere;

    /** ������ Ÿ�� */
    AActor* TargetActor;

    /** ���� �̺�Ʈ */
    UFUNCTION()
    void OnTargetDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    /** ������ ����� ������ ��� �� ȣ��Ǵ� �Լ� */
    UFUNCTION()
    void OnTargetLost(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    
    /** ������ ����ü Ŭ���� */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    TSubclassOf<class ATowerRushProjectileBase> ProjectileClass;

    /** ����ü �߻� ���� */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    float SpawnInterval = 2.0f;
};
