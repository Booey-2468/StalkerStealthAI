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
	
	UBTDecorator_IsInRange();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
