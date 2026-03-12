// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/EnvQueryContext_PlayerContext.h"

void UEnvQueryContext_PlayerContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	ACustomAIController* MyAIController = Cast<ACustomAIController>(Cast<AActor>(QueryInstance.Owner.Get())->GetInstigatorController());

	if (MyAIController && MyAIController->GetSeenPawn())
	{
		UBlackboardComponent* MyBlackboard = MyAIController->BlackboardComp;
		if (MyBlackboard)
		{
			UEnvQueryItemType_Actor::SetContextHelper(ContextData, MyAIController->GetSeenPawn());
		}
	}
}