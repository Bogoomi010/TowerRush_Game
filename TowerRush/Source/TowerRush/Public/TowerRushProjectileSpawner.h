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

    /** 일정 간격마다 투사체 생성 */
    void SpawnProjectile();

    /** 타이머 핸들 */
    FTimerHandle SpawnTimerHandle;

public:
    virtual void Tick(float DeltaTime) override;

    /** 생성할 투사체 클래스 */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    TSubclassOf<class ATowerRushProjectileBase> ProjectileClass;

    /** 투사체 발사 간격 */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    float SpawnInterval = 2.0f;
};