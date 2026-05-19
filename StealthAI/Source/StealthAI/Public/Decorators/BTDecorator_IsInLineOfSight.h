// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "StealthAIAgent.h"
#include "CustomAIController.h"

#include "BTDecorator_IsInLineOfSight.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class STEALTHAI_API UBTDecorator_IsInLineOfSight : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	/// <summary>
	/// Sets Name and confirms that the node will be instanced.
	/// </summary>
	UBTDecorator_IsInLineOfSight();

	/// <summary>
	/// Checks if the Pawn is in AI perception.
	/// </summary>
	/// <param name="OwnerComp"> Owner Comp is the needed for override and allows the getting of the AI controller, 
	/// BlackboardComp and the Pawn</param>
	/// <param name="NodeMemory"> Needed for override </param>
	/// <returns> Whether or not the player is in sight.</returns>
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
