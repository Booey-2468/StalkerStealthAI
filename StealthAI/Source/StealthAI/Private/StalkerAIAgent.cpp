// Fill out your copyright notice in the Description page of Project Settings.


#include "StalkerAIAgent.h"

// Sets default values
AStalkerAIAgent::AStalkerAIAgent()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = RootComp;

	RootComp = CreateDefaultSubobject<USceneComponent>("Root Component");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());

	PawnPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception");
	AIController = CreateDefaultSubobject<AAIController>("AI Controller");
	SetupAIPerception();

}
/// <summary>
/// Sets up AI Sight and Hearing uses the perception library stuff
/// </summary>
void AStalkerAIAgent::SetupAIPerception()
{
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");

	SightConfig->SightRadius = 300.0f;
	SightConfig->LoseSightRadius = 300.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;

	UAISenseConfig_Hearing* HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");
	HearingConfig->HearingRange = 500.0f;


	PawnPerception->ConfigureSense(*SightConfig);
	PawnPerception->ConfigureSense(*HearingConfig);

	SightID = SightConfig->GetSenseID();
	HearingID = HearingConfig->GetSenseID();
}

void AStalkerAIAgent::ChaseObjective(FVector ObjectiveLocation)
{
	ARecastNavMesh* NavMesh = GetNavmesh();

	AIController->MoveToLocation(ObjectiveLocation, 15.0f, true, true, true, true);
}

ARecastNavMesh* AStalkerAIAgent::GetNavmesh()
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (!NavSystem)
		return nullptr;

	return Cast<ARecastNavMesh>(NavSystem->GetDefaultNavDataInstance());
}

// Called when the game starts or when spawned
void AStalkerAIAgent::BeginPlay()
{
	Super::BeginPlay();
	if (PawnPerception)
	{
		PawnPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AStalkerAIAgent::UpdatePerceptionVariables);
	}
}

void AStalkerAIAgent::UpdatePerceptionVariables(AActor* PercievedActor, FAIStimulus Stimulus)
{
	if (Stimulus.Type == SightID)
	{
		IsInSight = true;
	}
	else if (Stimulus.Type == SightID && !Stimulus.SensingSucceeded)
	{

	}
	else if (Stimulus.Type == HearingID)
	{

	}
}

// Called every frame
void AStalkerAIAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
