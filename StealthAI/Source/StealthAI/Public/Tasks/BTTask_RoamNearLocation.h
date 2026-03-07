// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "CustomAIController.h"
#include "StealthAIAgent.h"
#include "StealthAI/StealthAICharacter.h"

#include "BTTask_RoamNearLocation.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTTask_RoamNearLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_RoamNearLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;



};
