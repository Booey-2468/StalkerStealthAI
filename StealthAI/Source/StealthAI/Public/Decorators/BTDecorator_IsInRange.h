// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"

#include "StealthAIAgent.h"
#include "CustomAIController.h"

#include "BTDecorator_IsInRange.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTDecorator_IsInRange : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	/// <summary>
	/// Sets Name and confirms that the node will be instanced.
	/// </summary>
	UBTDecorator_IsInRange();

	/// <summary>
	/// Checks if the AI Agent is within a specified range of the player based on blackboard values
	/// </summary>
	/// <param name="OwnerComp"> Owner Comp is the needed for override and allows the getting of the Blackboard. </param>
	/// <param name="NodeMemory"> Needed for override </param>
	/// <returns> Whether or not the player is out of the necessary range </returns>
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
