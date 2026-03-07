// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

#include "StealthAIAgent.h"
#include "CustomAIController.h"

#include "NavMesh/RecastNavMesh.h"

#include "Kismet/GameplayStatics.h"

#include "BTTask_MoveInRange.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTTask_MoveInRange : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UBTTask_MoveInRange();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
