// Fill out your copyright notice in the Description page of Project Settings.


#include "DBT_LineOfSight.h"

bool UDBT_LineOfSight::InLineOfSight(AStalkerAIAgent* AIAgent)
{
	return AIAgent->IsInSight;
}