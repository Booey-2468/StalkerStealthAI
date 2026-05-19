// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"

#include "CustomAIController.h"
#include "StealthAIAgent.h"
#include "StealthAI/StealthAICharacter.h"

#include "BTDecorator_ShouldPatrol.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTDecorator_ShouldPatrol : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	/// <summary>
	/// Sets Name and confirms that the node will be instanced.
	/// </summary>
	UBTDecorator_ShouldPatrol();

	/// <summary>
	/// Checks if the Pawn should be roaming.
	/// </summary>
	/// <param name="OwnerComp"> Owner Comp is the needed for override and allows the getting of the AI controller, 
	/// BlackboardComp and the Pawn</param>
	/// <param name="NodeMemory"> Needed for override </param>
	/// <returns> Whether or not roaming should be done.</returns>
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
