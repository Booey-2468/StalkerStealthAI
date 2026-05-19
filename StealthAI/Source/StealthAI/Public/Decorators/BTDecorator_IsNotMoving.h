// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"

#include "StealthAIAgent.h"
#include "CustomAIController.h"

#include "BTDecorator_IsNotMoving.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTDecorator_IsNotMoving : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	/// <summary>
	/// Sets Name and confirms that the node will be instanced.
	/// </summary>
	UBTDecorator_IsNotMoving();

	/// <summary>
	/// Checks if the AI Agent has finished moving so things are done only after previous movement is complete.
	/// </summary>
	/// <param name="OwnerComp"> Owner Comp is the needed for override and allows the getting of the AI controller, 
	/// BlackboardComp and the Pawn</param>
	/// <param name="NodeMemory"> Needed for override </param>
	/// <returns> Whether or not the AI has finished moving.</returns>
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
