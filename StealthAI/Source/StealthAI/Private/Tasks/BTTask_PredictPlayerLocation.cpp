// Fill out your copyright notice in the Description page of Project Settings.


#include "Tasks/BTTask_PredictPlayerLocation.h"

UBTTask_PredictPlayerLocation::UBTTask_PredictPlayerLocation()
{
	NodeName = "Predict Possible Player Location";
	bCreateNodeInstance = true;
}

EBTNodeResult::Type UBTTask_PredictPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent();
	ACustomAIController* MyAIController = Cast<ACustomAIController>(OwnerComp.GetAIOwner());

	if (!MyBlackboard || !MyAIController || !Cast<AStealthAIAgent>(MyAIController->GetPawn()))
	{
		return EBTNodeResult::Type::Failed;
	}
	
	float DeltaSeenTime = MyBlackboard->GetValueAsFloat("PlayerSeenTime") - MyBlackboard->GetValueAsFloat("PlayerSeenTimer");
	FVector PlayerVelocity = MyBlackboard->GetValueAsVector("PlayerVelocity");
	float RandomAngle = FMath::RandRange(-90, 90) * PI/180;
	
	// Uses Rodrigues' Formula which is used for rotating a vector around an axis
	FVector RotatedVelocity = PlayerVelocity * FMath::Cos(RandomAngle) +
		FVector::CrossProduct(FVector::UpVector, PlayerVelocity) * FMath::Sin(RandomAngle) +
		FVector::UpVector * FVector::DotProduct(FVector::UpVector, PlayerVelocity) * (1.0f - FMath::Cos(RandomAngle));
	
	FVector VelDir = RotatedVelocity;
	VelDir.Normalize();
	RotatedVelocity = VelDir * (RotatedVelocity * DeltaSeenTime);

	if (RotatedVelocity.Length() > MyBlackboard->GetValueAsFloat("MaxVelocityRadii"))
	{
		RotatedVelocity = VelDir * MyBlackboard->GetValueAsFloat("MaxVelocityRadii");
	}

	MyBlackboard->SetValueAsVector("TargetLocation", RotatedVelocity);

	return EBTNodeResult::Type::Succeeded;

}
