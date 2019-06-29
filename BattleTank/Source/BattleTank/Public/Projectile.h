// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

	void LaunchProjectile(float Speed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Params")
		float ProjectileVelocity = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Params")
		float ProjectileTTL = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Params")
		float ProjectileDamage = 0.0f;

private:
	UPROPERTY(VisibleAnywhere, Category = "Default Subobjects")
	UStaticMeshComponent* CollisionMesh;

	UPROPERTY(VisibleAnywhere, Category = "Default Subobjects")
	UParticleSystemComponent* LaunchBlast;

	UPROPERTY(VisibleAnywhere, Category = "Default Subobjects")
	UParticleSystemComponent* ImpactBlast;

	UPROPERTY(VisibleAnywhere, Category = "Default Subobjects")
	URadialForceComponent* BlastForce;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditDefaultsOnly, Category = "Destruction Parameters")
	float DestroyDelay = 0.3;

	void OnTimerExpire();




};
