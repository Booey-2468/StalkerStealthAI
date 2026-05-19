// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "StealthAIAgent.h"
#include "CustomAIController.h"

#include "StealthAI/StealthAICharacter.h"

#include "BTService_OnSeenPlayer.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTService_OnSeenPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
	/// <summary>
	/// Sets Name and confirms that the node will be instanced.
	/// </summary>
	UBTService_OnSeenPlayer();

	/// <summary>
	/// Updates sight based blackboard information after being seen.
	/// </summary>
	/// <param name="OwnerComp"> Used for getting AI controller, blackboard, AI agent and Player pointers. </param>
	/// <param name="NodeMemory"> Used for override. </param>
	/// <param name="DeltaSeconds"> Used for override. </param>
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
