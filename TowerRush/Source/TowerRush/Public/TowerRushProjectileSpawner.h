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

public:
    virtual void Tick(float DeltaTime) override;

    /** ������ ����ü Ŭ���� */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    TSubclassOf<class ATowerRushProjectileBase> ProjectileClass;

    /** ����ü �߻� ���� */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    float SpawnInterval = 2.0f;
};