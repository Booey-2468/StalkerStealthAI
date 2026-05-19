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
	
	/// <summary>
	/// Sets Name and confirms that the node will be instanced.
	/// </summary>
	UBTService_OnHeardPlayer();

	/// <summary>
	/// Updates hearing based blackboard information after being heard.
	/// </summary>
	/// <param name="OwnerComp"> </param>
	/// <param name="NodeMemory"> Used for override. </param>
	/// <param name="DeltaSeconds"> Used for override. </param>
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
