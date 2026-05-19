// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnableBullet.generated.h"

UCLASS()
class ASpawnableBullet : public AActor
{
	GENERATED_BODY()
	
	// Sets default values for the bullet's properties
	ASpawnableBullet();
public:	
	void Initialize(UStaticMesh* BulletMesh);

	float BulletTime = 0.0f;
	float BulletTimer = 0.0f;
	
	UStaticMeshComponent* MeshRoot;	// Pointer to Root Component Static mesh comp

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
