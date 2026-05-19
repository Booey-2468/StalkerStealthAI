// Fill out your copyright notice in the Description page of Project Settings.


#include "EQS/EnvQueryTest_TestForNearbyHit.h"

UEnvQueryTest_TestForNearbyHit::UEnvQueryTest_TestForNearbyHit()
{
	Cost = EEnvTestCost::Low;
	TestPurpose = EEnvTestPurpose::Score;
	ValidItemType = UEnvQueryItemType_Point::StaticClass();
	SetWorkOnFloatValues(false);
}
void UEnvQueryTest_TestForNearbyHit::RunTest(FEnvQueryInstance& QueryInstance) const
{
	ACustomAIController* MyAIController = Cast<ACustomAIController>(Cast<AActor>(QueryInstance.Owner.Get())->GetInstigatorController());

	if (!MyAIController || !MyAIController->GetWorld())		// Ensures AI controller and World is valid before
		return;

	AStealthAICharacter* Player = Cast<AStealthAICharacter>(MyAIController->GetSeenPawn());

	if (!Player)	// Ensures Player pointer is valid
		return;

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		FHitResult Hit = FHitResult();

		FVector Start = QueryInstance.GetItemAsLocation(It.GetIndex());	// Gets Item's location and adds height offset to it as start point
		Start += FVector::UpVector * HeightOffset;

		FVector End = Start - Player->GetActorLocation();
		End = FVector::VectorPlaneProject(End, FVector::UpVector);	// Projects vector along plane to get direction along XY plane
		End.Normalize();
		FVector PlayerDir = End;
		//Ensures end is just a normalized direction
		End = Start + End * TraceLength;	// Multiplies end dir by trace length and adds to start location

		// Sweeps capsule from start to end and stores in hit, then sets score based on blocking hit
		MyAIController->GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_WorldStatic, FCollisionShape::MakeCapsule(MyAIController->GetPawn()->GetSimpleCollisionRadius(), MyAIController->GetPawn()->GetDefaultHalfHeight()));
		
		if (Hit.Normal.Dot(PlayerDir) > 0.1)
		{
			
		}
		It.SetScore(TestPurpose, FilterType, Hit.bBlockingHit, true);
	}

}