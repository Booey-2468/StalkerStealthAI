// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/EnvQueryGenerator_SurroundCone.h"

void UEnvQueryGenerator_SurroundCone::GenerateItems(FEnvQueryInstance& QueryInstance) const
{
	TArray<FNavLocation> ItemCandidates;
	AStealthAIAgent* MyAIAgent = Cast<AStealthAIAgent>(QueryInstance.Owner.Get());
	if (!MyAIAgent || AngleStep.GetValue() == 0)	// Makes sure agent and angle step is valid so no infinite loop or invalid error
	{
		return;
	}

	FVector AgentLocation = MyAIAgent->GetActorLocation();
	FVector AgentForward = MyAIAgent->GetActorForwardVector();	// Gets the agents current location and forward vector
	// Switched for loop setup which first did one row and then the next row for each cone degree
	for (int32 Point = 0; Point < ConeRadius; Point++)
	{	
		for (float Angle = -ConeDegrees.GetValue(); Angle < ConeDegrees.GetValue(); Angle += AngleStep.GetValue()) 
		{
			if (Point == 0)	// This allows saving memory with a large amount of accuracy remaining by not generating unnecessary items and gradually increasing accuracy the further out is gone
				Angle = 180;
			else if (Point < 2)
				Angle += 50;
			else if (Point < 4)
				Angle += 20;
			else if (Point > 10)	// Used arbitrary numbers based on testing what looked most accurate with the least amount of tests
				Angle -= 5;

			float RadAngle = (Angle)*PI / 180;	// Converts from degrees to Radians
			
			FVector NewAngleVector = AgentForward * FMath::Cos(RadAngle) +
				FVector::CrossProduct(FVector::UpVector, AgentForward) * FMath::Sin(RadAngle) +
				FVector::UpVector * FVector::DotProduct(FVector::UpVector, AgentForward) * (1.0f - FMath::Cos(RadAngle));				

			FNavLocation NavLoc = FNavLocation(AgentLocation + NewAngleVector * Point * PointsDist);
			ItemCandidates.Add(NavLoc);
		}
	}
	ProjectAndFilterNavPoints(ItemCandidates, QueryInstance);	// Project all nav points to the Navmesh and store the results
	StoreNavPoints(ItemCandidates, QueryInstance);
}
