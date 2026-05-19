// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableBullet.h"

// Sets default values
ASpawnableBullet::ASpawnableBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshRoot = CreateDefaultSubobject<UStaticMeshComponent>("Bullet Mesh");
	RootComponent = MeshRoot;
	MeshRoot->SetVisibility(false);
}

void ASpawnableBullet::Initialize(UStaticMesh* BulletMesh)
{
	MeshRoot->SetStaticMesh(BulletMesh);
	MeshRoot->SetWorldScale3D(FVector(2));	// Sets scale in order to be able to better see the Bullet mesh
	//Enables Physics Collision settings

	// Changes response to pawns from block to overlap to avoid physics collisions
	MeshRoot->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	// Changes response to camera to overlap to avoid camera spring arm from
	MeshRoot->SetCollisionResponseToChannel(ECC_Camera, ECR_Overlap);
}
// Called when the game starts or when spawned
void ASpawnableBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnableBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (BulletTime > 0.0f)	// If Bullet Time has been set then start counting down
	{
		if (BulletTimer > 0)
		{
			BulletTimer -= DeltaTime;
		}
		else
		{	// Only occurs when timer is up disabling the object
			MeshRoot->SetSimulatePhysics(false);
			MeshRoot->SetVisibility(false);		// Disables the object after the bullet's life timer has expired

			BulletTime = 0.0f;	// Resets timer values
			BulletTimer = 0.0f;
		}
	}

}

