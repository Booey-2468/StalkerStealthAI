// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/EnvQueryGenerator_SurroundCone.h"

void UEnvQueryGenerator_SurroundCone::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	TArray<FNavLocation> ItemCandidates;
	AStealthAIAgent* MyAIAgent = Cast<AStealthAIAgent>(QueryInstance.Owner.Get());
	if (!MyAIAgent || AngleStep.GetValue() == 0)
	{
		return;
	}

	FVector AgentLocation = MyAIAgent->GetActorLocation();
	FVector AgentForward = MyAIAgent->GetActorForwardVector();

	for (float Angle = -ConeDegrees.GetValue(); Angle < ConeDegrees.GetValue(); Angle += AngleStep.GetValue())
	{
		FVector NewAngleVector = AgentForward * FMath::Cos(Angle + 1) +
			(FVector::UpVector * AgentForward) * FMath::Sin(Angle + 1) +
			FVector::UpVector * FVector::DotProduct(FVector::UpVector, AgentForward) * (1.0f - FMath::Cos(Angle + 1));
		for (int32 Point = 0; Point < ConeRadius; Point++)
		{
			FNavLocation NavLoc = FNavLocation(AgentLocation + NewAngleVector * Point * PointsDist);
			ItemCandidates.Add(NavLoc);
		}
	}
	ProjectAndFilterNavPoints(ItemCandidates, QueryInstance);
	StoreNavPoints(ItemCandidates, QueryInstance);
}
