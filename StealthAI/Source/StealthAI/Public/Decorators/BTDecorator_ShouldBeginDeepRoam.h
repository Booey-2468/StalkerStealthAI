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

	UBTDecorator_ShouldBeginDeepRoam();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
