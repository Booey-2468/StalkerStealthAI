// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"

#include "CustomAIController.h"
#include "StealthAI/StealthAICharacter.h"

#include "DrawDebugHelpers.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"

#include "EnvQueryTest_TestForNearbyHit.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UEnvQueryTest_TestForNearbyHit : public UEnvQueryTest
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = TraceDetails)
	float TraceLength = 200.0f;	// Length of capsule trace

	UPROPERTY(EditAnywhere, Category = TraceDetails)
	float HeightOffset = 90.0f;	// Height offset from item/floor

	/// <summary>
	/// Sets up the test to be recpognized by the EQS blueprint.
	/// </summary>
	UEnvQueryTest_TestForNearbyHit();
	
	/// <summary>
	/// Tests to see if agent would collide with static meshes in that area to check if the player would have cover or not.
	/// </summary>
	/// <param name="QueryInstance"> Used for override and getting AI controller owner as well as player data. </param>
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
