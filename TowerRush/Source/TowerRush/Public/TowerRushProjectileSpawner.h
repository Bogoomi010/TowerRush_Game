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

    /** 감지 범위 */
    UPROPERTY(VisibleAnywhere, Category = "Detection")
    class USphereComponent* DetectionSphere;

    /** 감지된 타겟 */
    AActor* TargetActor;

    /** 감지 이벤트 */
    UFUNCTION()
    void OnTargetDetected(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    /** 감지된 대상이 범위를 벗어날 때 호출되는 함수 */
    UFUNCTION()
    void OnTargetLost(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
    
    /** 생성할 투사체 클래스 */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    TSubclassOf<class ATowerRushProjectileBase> ProjectileClass;

    /** 투사체 발사 간격 */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    float SpawnInterval = 2.0f;
};
