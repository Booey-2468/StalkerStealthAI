// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"

#include "CustomAIController.h"
#include "StealthAIAgent.h"

#include "BTDecorator_HasPlayerMoved.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTDecorator_HasPlayerMoved : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
	/// <summary>
	/// Sets Name and confirms that the node will be instanced.
	/// </summary>
	UBTDecorator_HasPlayerMoved();

	/// <summary>
	/// Checks if the Player has moved a certain amount before running SQL query.
	/// </summary>
	/// <param name="OwnerComp"> Owner Comp is the needed for override and allows the getting of the AI controller, 
	/// BlackboardComp and the Pawn</param>
	/// <param name="NodeMemory"> Needed for override </param>
	/// <returns> Whether or not the player has moved a fair amount.</returns>
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
