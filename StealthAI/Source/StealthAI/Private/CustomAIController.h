// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StalkerAIAgent.h"
#include "CustomAIController.generated.h"

/**
 * 
 */
UCLASS()
class ACustomAIController : public AAIController
{
	GENERATED_BODY()


	virtual void OnPossess(APawn* InPawn) override;
};
