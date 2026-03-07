// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"

#include "CustomAIController.h"
#include "StealthAIAgent.h"
#include "StealthAI/StealthAICharacter.h"

#include "BTDecorator_ShouldRoam.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UBTDecorator_ShouldRoam : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
	UBTDecorator_ShouldRoam();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;


};
