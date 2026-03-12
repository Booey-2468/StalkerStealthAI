// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAIController.h"

ACustomAIController::ACustomAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>("Black Board");
	BehaviourTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("Behaviour Tree");

	PawnPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception");
	SetPerceptionComponent(*PawnPerception);


	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");

	SightConfig->SightRadius = 3000.0f;
	SightConfig->LoseSightRadius = 2200.0f;
	SightConfig->PeripheralVisionAngleDegrees = 45.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");

	HearingConfig->HearingRange = 5000.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PawnPerception->ConfigureSense(*SightConfig);
	PawnPerception->ConfigureSense(*HearingConfig);
	PawnPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	bAllowStrafe = true;
}

void ACustomAIController::BeginPlay()
{
	Super::BeginPlay();

	if (PawnPerception)
	{
		PawnPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ACustomAIController::UpdatePerceptionVariables);
	}
}

APawn* ACustomAIController::GetSeenPawn()
{
	UObject* SeenPawn = BlackboardComp->GetValueAsObject("EnemyActor");
	return (SeenPawn) ? Cast<APawn>(SeenPawn) : nullptr;
}

void ACustomAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AStealthAIAgent* MyAIAgent = Cast<AStealthAIAgent>(InPawn);

	SightID = SightConfig->GetSenseID();
	HearingID = HearingConfig->GetSenseID();

	if (BlackboardComp && BehaviourTreeComp)
	{
		BlackboardComp->InitializeBlackboard(*MyAIAgent->BehaviourTree->BlackboardAsset);
		BehaviourTreeComp->StartTree(*MyAIAgent->BehaviourTree);
	}
	this->SetControlRotation(MyAIAgent->GetActorRotation());
}

void ACustomAIController::UpdatePerceptionVariables(AActor* PercievedActor, FAIStimulus Stimulus)
{
	AStealthAICharacter* PlayerCharacter = Cast<AStealthAICharacter>(PercievedActor);
	if (Stimulus.Type == SightID && Stimulus.WasSuccessfullySensed() && PlayerCharacter)
	{
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsObject("EnemyActor", PlayerCharacter);
		}
	}
	else if (Stimulus.Type == SightID && !Stimulus.WasSuccessfullySensed())
	{
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsObject("EnemyActor", nullptr);
		}
	}
	else if (Stimulus.Type == HearingID && Stimulus.SensingSucceeded && PlayerCharacter)
	{
		
	}
}

void ACustomAIController::Tick(float DeltaTime)
{	
	if (BlackboardComp->GetValueAsBool("IsAlert") && BlackboardComp->GetValueAsFloat("AlertStateTimer") > 0)
	{
		BlackboardComp->SetValueAsFloat("AlertStateTimer", BlackboardComp->GetValueAsFloat("AlertStateTimer") - DeltaTime);
	}
	else if (BlackboardComp->GetValueAsBool("IsAlert"))
	{
		BlackboardComp->SetValueAsBool("IsAlert", false);
		BlackboardComp->SetValueAsFloat("AlertStateTimer", 0.0f);	// Disables the Alert State and Enables Roaming Mode

		BlackboardComp->SetValueAsBool("IsRecentlyDetected", true);
		BlackboardComp->SetValueAsFloat("PlayerSeenTimer", BlackboardComp->GetValueAsFloat("PlayerSeenTime"));
	}
	//Timer for Roaming sets Is recently detected to false and sets timer to 0 once timer is up allowing for patrolling
	if (BlackboardComp->GetValueAsBool("IsRecentlyDetected") && BlackboardComp->GetValueAsFloat("PlayerSeenTimer") > 0)
	{
		BlackboardComp->SetValueAsFloat("PlayerSeenTimer", BlackboardComp->GetValueAsFloat("PlayerSeenTimer") - DeltaTime);
	}
	else if (BlackboardComp->GetValueAsBool("IsRecentlyDetected"))
	{
		BlackboardComp->SetValueAsBool("IsRecentlyDetected", false);
		BlackboardComp->SetValueAsFloat("PlayerSeenTimer", 0.0f);
	}

	// Checks Agent no longer needs to be in deeper roaming when roaming is over or the player has been seen
	if(Cast<AStealthAICharacter>(GetSeenPawn()) || !BlackboardComp->GetValueAsBool("IsRecentlyDetected"))
	{
		BlackboardComp->SetValueAsBool("ShouldStartInDepthRoaming", false);
	}
}

void ACustomAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);	// Does normal OnMoveCompleted stuff then checks whether pawn has not been seen and is recently detected
	// To check if deep roaming should start uses when move completed so AI gets to intial last known location before happening
	if (!Cast<AStealthAICharacter>(GetSeenPawn()) && BlackboardComp->GetValueAsBool("IsRecentlyDetected"))
	{
		BlackboardComp->SetValueAsBool("ShouldStartInDepthRoaming", true);
	}
	if (BlackboardComp->GetValueAsBool("IsTakingCover"))
	{
		BlackboardComp->SetValueAsBool("IsTakingCover", false);
	}
}