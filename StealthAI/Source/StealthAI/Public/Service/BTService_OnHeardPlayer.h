// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

#include "StealthAIAgent.h"
#include "CustomAIController.h"

#include "StealthAI/StealthAICharacter.h"

#include "NavMesh/RecastNavMesh.h"

#include "BTService_OnHeardPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTService_OnHeardPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	UBTService_OnHeardPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
