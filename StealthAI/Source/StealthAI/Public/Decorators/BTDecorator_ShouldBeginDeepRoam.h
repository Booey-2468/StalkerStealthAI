// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"

#include "StealthAIAgent.h"
#include "CustomAIController.h"

#include "BTDecorator_ShouldBeginDeepRoam.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTDecorator_ShouldBeginDeepRoam : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	/// <summary>
	/// Sets Name and confirms that the node will be instanced.
	/// </summary>
	UBTDecorator_ShouldBeginDeepRoam();

	/// <summary>
	/// Checks if the Pawn is ready to go into deep roaming which predicts player location based on randomness and velocity.
	/// </summary>
	/// <param name="OwnerComp"> Owner Comp is the needed for override and allows the getting of the AI controller, 
	/// BlackboardComp and the Pawn</param>
	/// <param name="NodeMemory"> Needed for override </param>
	/// <returns> Whether or not in depth roaming should begin.</returns>
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
