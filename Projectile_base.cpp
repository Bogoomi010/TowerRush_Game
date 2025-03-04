#include "Projectile_base.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Enemy_base.h"
#include "Engine/Engine.h"


AProjectile_base::AProjectile_base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
    RootComponent = ProjectileMesh;

    // Static Mesh 설정
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/FantasyInterior01/Meshes/SM_Apple_03"));
    if (ProjectileMeshAsset.Succeeded())
    {
        ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
    }

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = ProjectileMesh;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    Damage = 20.f;

    ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile_base::OnHit);
}

// Called when the game starts or when spawned
void AProjectile_base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile_base::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        AEnemy_base* HitEnemy = Cast<AEnemy_base>(OtherActor);
        if (HitEnemy)
        {
            HitEnemy->TakeDamage(Damage);

            // 화면에 로그 메시지 출력
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit enemy: %s"), *HitEnemy->GetName()));
            }
        }

        // 발사체 제거
        Destroy();
    }
}

