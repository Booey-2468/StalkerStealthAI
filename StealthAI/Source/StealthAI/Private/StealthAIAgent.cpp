// Fill out your copyright notice in the Description page of Project Settings.


#include "StealthAIAgent.h"

// Sets default values
AStealthAIAgent::AStealthAIAgent()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = RootComp;

	RootComp = CreateDefaultSubobject<USceneComponent>("Root Component");

	PawnPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception");
	AIController = CreateDefaultSubobject<AAIController>("AI Controller");
	SetupAIPerception();

}
/// <summary>
/// Sets up AI Sight and Hearing uses the perception library stuff
/// </summary>
void AStealthAIAgent::SetupAIPerception()
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

void AStealthAIAgent::ChaseObjective(FVector ObjectiveLocation)
{
	ARecastNavMesh* NavMesh = GetNavmesh();

	AIController->MoveToLocation(ObjectiveLocation, 15.0f, true, true, true, true);
}

ARecastNavMesh* AStealthAIAgent::GetNavmesh()
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (!NavSystem)
		return nullptr;

	return Cast<ARecastNavMesh>(NavSystem->GetDefaultNavDataInstance());
}

// Called when the game starts or when spawned
void AStealthAIAgent::BeginPlay()
{
	Super::BeginPlay();
	if (PawnPerception)
	{
		PawnPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AStealthAIAgent::UpdatePerceptionVariables);
	}
}

void AStealthAIAgent::UpdatePerceptionVariables(AActor* PercievedActor, FAIStimulus Stimulus)
{
	AStealthAICharacter* PlayerCharacter = Cast<AStealthAICharacter>(PercievedActor);
	if (Stimulus.Type == SightID && Stimulus.SensingSucceeded && PlayerCharacter)
	{
		IsInSight = true;
	}
	else if (Stimulus.Type == SightID && !Stimulus.SensingSucceeded)
	{

	}
	else if (Stimulus.Type == HearingID && Stimulus.SensingSucceeded && PlayerCharacter)
	{

	}
}

// Called every frame
void AStealthAIAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


