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
	float PointsDist = 50.0f;

	UPROPERTY(EditAnywhere, Category = ConeProperties)
	float ConeRadius = 50.0f;
public:
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;
};
