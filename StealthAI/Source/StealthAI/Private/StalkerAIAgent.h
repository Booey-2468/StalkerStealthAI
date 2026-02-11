// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "StalkerAIAgent.generated.h"

UCLASS()
class AStalkerAIAgent : public APawn
{
	GENERATED_BODY()
	UStaticMeshComponent* Mesh;

public:
	// Sets default values for this pawn's properties
	AStalkerAIAgent();
	void ChaseObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
