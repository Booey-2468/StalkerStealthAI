// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_Cone.h"

#include "StealthAIAgent.h"

#include "EnvQueryGenerator_SurroundCone.generated.h"

/**
 * 
 */
UCLASS()
class STEALTHAI_API UEnvQueryGenerator_SurroundCone : public UEnvQueryGenerator_Cone
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = ConeProperties)
	float PointsDist = 50.0f;	// Distance between points

	UPROPERTY(EditAnywhere, Category = ConeProperties)
	float ConeRadius = 50.0f;	// Radius of cone 



public:
	/// <summary>
	/// Generates a cone of EQS items in a cone I generally only use it in a circle though
	/// </summary>
	/// <param name="QueryInstance">Used in override and for getting owner pawn.</param>
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;
};
