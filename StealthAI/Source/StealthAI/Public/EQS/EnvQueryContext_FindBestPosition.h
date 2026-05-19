// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"

#include "CustomAIController.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "EnvQueryContext_FindBestPosition.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UEnvQueryContext_FindBestPosition : public UEnvQueryContext
{
	GENERATED_BODY()
	
	/// <summary>
	/// Used to set the context helper to current target location for other tests such as distance to target location
	/// </summary>
	/// <param name="QueryInstance"> Used for override. </param>
	/// <param name="ContextData"> Used for override. </param>
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

};
