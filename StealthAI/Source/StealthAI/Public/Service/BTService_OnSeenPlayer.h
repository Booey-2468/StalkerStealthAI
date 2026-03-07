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

#include "BTService_OnSeenPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTService_OnSeenPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	UBTService_OnSeenPlayer();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
