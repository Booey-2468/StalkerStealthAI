// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAIController.h"

#pragma region AI&PerceptionSetup

ACustomAIController::ACustomAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>("Black Board");
	BehaviourTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("Behaviour Tree");

	PawnPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception");
	SetPerceptionComponent(*PawnPerception);


	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");

	SightConfig->SightRadius = 2500.0f;
	SightConfig->LoseSightRadius = 3000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 60.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>("Hearing Config");

	HearingConfig->HearingRange = 5000.0f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
	HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
	HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PawnPerception->ConfigureSense(*SightConfig);	// Configures senses according to sense config and sets sight as the dominant sense
	PawnPerception->ConfigureSense(*HearingConfig);
	PawnPerception->SetDominantSense(SightConfig->GetSenseImplementation());

	bAllowStrafe = true;

	// Creates default audio comp for playing audio
	GunFireComp = CreateDefaultSubobject<UAudioComponent>("Shooting Audio Player");
	GunFireComp->bCanPlayMultipleInstances = false;
	// Allows multiple audio to play at one time

	FootstepsComp = CreateDefaultSubobject<UAudioComponent>("Walking Audio Player");
	FootstepsComp->bCanPlayMultipleInstances = false;
}

void ACustomAIController::BeginPlay()
{
	Super::BeginPlay();

	if (PawnPerception)
	{
		PawnPerception->OnTargetPerceptionUpdated.AddDynamic(this, &ACustomAIController::UpdatePerceptionVariables);
	}
	ShootBulletEventDispatcher.AddUniqueDynamic(this, &ACustomAIController::ShootBullet);
}
#pragma endregion
APawn* ACustomAIController::GetSeenPawn()
{
	UObject* SeenPawn = BlackboardComp->GetValueAsObject("EnemyActor");
	return (SeenPawn) ? Cast<APawn>(SeenPawn) : nullptr;
}

void ACustomAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MyAgent = Cast<AStealthAIAgent>(InPawn);

	if (MyAgent->FootstepsSound)	// Sets the pawns stored sounds
		FootstepsComp->SetSound(MyAgent->FootstepsSound);

	if(MyAgent->ShootingSound)
		GunFireComp->SetSound(MyAgent->ShootingSound);

	SightID = SightConfig->GetSenseID();
	HearingID = HearingConfig->GetSenseID();	// Ensures Sight and Hearing ID has sense Config ID  set 

	if (BlackboardComp && BehaviourTreeComp)	// Starts up AI Agent's Behaviour tree and black board
	{
		BlackboardComp->InitializeBlackboard(*MyAgent->BehaviourTree->BlackboardAsset);
		BehaviourTreeComp->StartTree(*MyAgent->BehaviourTree);
	}
	this->SetControlRotation(MyAgent->GetActorRotation());

	for (int i = 0; i <= BlackboardComp->GetValueAsInt("MaxAmmo"); i++)	// Spawns and Initializes all Bullets and is added to Spawned Bullets Array
	{
		ASpawnableBullet* Bullet = GetWorld()->SpawnActor<ASpawnableBullet>(ASpawnableBullet::StaticClass(), FVector(0), FVector::UpVector.Rotation());
		Bullet->Initialize(MyAgent->BulletMesh);
		SpawnedBullets.Emplace(Bullet);
	}
}
#pragma region Perception
void ACustomAIController::UpdatePerceptionVariables(AActor* PercievedActor, FAIStimulus Stimulus)
{
	AStealthAICharacter* PlayerCharacter = Cast<AStealthAICharacter>(PercievedActor);
	if (Stimulus.Type == SightID && Stimulus.WasSuccessfullySensed() && PlayerCharacter)
	{
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsObject("EnemyActor", PlayerCharacter);	// Sets Player as seen actor
		}
	}
	else if (Stimulus.Type == SightID && !Stimulus.WasSuccessfullySensed())
	{
		if (BlackboardComp)
		{
			BlackboardComp->SetValueAsObject("EnemyActor", nullptr);	// Nullifies actor so that it is no longer adressed and there are no issues
		}
	}
	else if (Stimulus.Type == HearingID && Stimulus.WasSuccessfullySensed() && PlayerCharacter)
	{
		BlackboardComp->SetValueAsBool("HasHeard", true);
		BlackboardComp->SetValueAsVector("LastDetectedLocation", Stimulus.StimulusLocation);
	}
}
#pragma endregion


void ACustomAIController::Tick(float DeltaTime)
{	
	if (BlackboardComp->GetValueAsBool("IsShooting") && FiringTimer <= 0)
	{
		ShootBulletEventDispatcher.Broadcast();
	}
	else if (BlackboardComp->GetValueAsBool("IsShooting") && FiringTimer > 0)
	{
		FiringTimer -= DeltaTime;
	}
	
	if (GetPathFollowingComponent()->GetStatus() == EPathFollowingStatus::Moving && !WasMoving)
	{
		WasMoving = true;
		FootstepsComp->Play();

	}
	else if ((GetPathFollowingComponent()->GetStatus() == EPathFollowingStatus::Idle || GetPathFollowingComponent()->GetStatus() == EPathFollowingStatus::Waiting) && WasMoving)
	{
		WasMoving = false;
		FootstepsComp->Stop();
	}

	if (BlackboardComp->GetValueAsBool("UseCustomRot"))	// Allows turning without interfering with behaviour tree functionality
	{
		FQuat TargetQuat = BlackboardComp->GetValueAsRotator("TargetRotation").Quaternion();
		FQuat CurrentQuat = MyAgent->GetActorRotation().Quaternion();
		if ((TargetQuat - CurrentQuat).Rotator().IsNearlyZero())
		{
			BlackboardComp->SetValueAsBool("UseCustomRot", false);
		}
		else
		{
			MyAgent->SetActorRotation(FQuat::FastLerp(MyAgent->GetActorRotation().Quaternion(), TargetQuat, TurnSpeed), ETeleportType::TeleportPhysics);
		}
	}

	float AlertTimer = BlackboardComp->GetValueAsFloat("AlertStateTimer");
	bool IsAlert = BlackboardComp->GetValueAsBool("IsAlert");
	if (IsAlert && AlertTimer > 0)	// Checks if alert timer is active and if so starts counting down unless timer is less or equal to 0
	{
		AlertTimer -= DeltaTime;
		BlackboardComp->SetValueAsFloat("AlertStateTimer", AlertTimer);
	}
	else if (IsAlert)
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

		BlackboardComp->SetValueAsBool("IsPatrolling", true);
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
}

void ACustomAIController::ShootBullet()
{
	// Gets point approximately gun length in front of player as getting a scene component in the Blueprint is something you cannot do.
	FVector SpawnLocation = MyAgent->GetActorLocation() + MyAgent->GunPoint + MyAgent->GetActorForwardVector() * 100.0f;

	FVector StraightShootingDir;
	APawn* SeenPawn = GetSeenPawn();
	if (SeenPawn != nullptr)
	{
		StraightShootingDir = (SeenPawn->GetActorLocation() + SeenPawn->GetActorUpVector() * SeenPawn->GetDefaultHalfHeight()/2) - SpawnLocation;
		StraightShootingDir.Normalize();	// Accounts for player scale when shrinking to aim for roughly the chest area that is why I divide halfheight by 2
	}
	else
		StraightShootingDir = MyAgent->GetActorForwardVector();	// If shooting while player is not visible then just shoot in front of self


	float HortSpread = BlackboardComp->GetValueAsFloat("HorizontalSpread");	// Gets max spread in degrees as easier to visualize
	float VertSpread = BlackboardComp->GetValueAsFloat("VerticalSpread");

	HortSpread = FMath::RandRange(-HortSpread, HortSpread) * PI / 180;	// Gets random spread within range and rotates original direction vector to those degrees
	VertSpread = FMath::RandRange(-VertSpread, VertSpread) * PI / 180;	// Converted to radians as thats what Rodriguexz' formula uses as do most programmers

	FVector RotatedHortVector = StraightShootingDir * FMath::Cos(HortSpread) +
		FVector::CrossProduct(FVector::UpVector, StraightShootingDir) * FMath::Sin(HortSpread) +
		FVector::UpVector * FVector::DotProduct(FVector::UpVector, StraightShootingDir) * (1.0f - FMath::Cos(HortSpread));

	FVector RotatedVertVector = StraightShootingDir * FMath::Cos(VertSpread) +
		FVector::CrossProduct(FVector::RightVector, StraightShootingDir) * FMath::Sin(VertSpread) +
		FVector::RightVector * FVector::DotProduct(FVector::RightVector, StraightShootingDir) * (1.0f - FMath::Cos(VertSpread));

	FVector ShootingForce = RotatedHortVector + RotatedVertVector;	// Adds Both random vert and hort vectors to get the correct shooting vector
	ShootingForce.Normalize();	// Ensures the vector is fully a direction
	
	ASpawnableBullet* Bullet = SpawnedBullets[CurrentBullet].Get();
	// Checks if Bullet Assignment is null/bad 
	if(Bullet)
	{
		//Checks if Bullet is bad after assignment as some extra pointer handling
		if (Bullet == nullptr || !IsValid(Bullet) || !SpawnedBullets.IsValidIndex(CurrentBullet))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Error: Dead Pointer Found after checking");
			Bullet = GetWorld()->SpawnActor<ASpawnableBullet>(ASpawnableBullet::StaticClass(), FVector(0), FVector::UpVector.Rotation());
			Bullet->Initialize(MyAgent->BulletMesh);
			SpawnedBullets[CurrentBullet] = Bullet;	// Spawns new bullet initializes it with correct physics settings and assigns it to array
		}
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Error: Dead Pointer Found at Assignment");
		Bullet = GetWorld()->SpawnActor<ASpawnableBullet>(ASpawnableBullet::StaticClass(), FVector(0), FVector::UpVector.Rotation());
		Bullet->Initialize(MyAgent->BulletMesh);
		SpawnedBullets[CurrentBullet] = Bullet;	// Spawns new bullet initializes it with correct physics settings and assigns it to array
	}
	EnableBulletVisuals(*Bullet, SpawnLocation, ShootingForce);	//Increments to Next Bullet and Activates it
	CurrentBullet = (CurrentBullet >= SpawnedBullets.Num() - 1) ? 0 : CurrentBullet + 1;	// Allows iterator to wrap around when limit is reached
	FiringTimer = BlackboardComp->GetValueAsFloat("FireRate");
	ShootingForce.Normalize();
	BulletLogic(SpawnLocation, ShootingForce, BlackboardComp->GetValueAsFloat("BulletDamage"));
}

void ACustomAIController::EnableBulletVisuals(ASpawnableBullet& Bullet, const FVector& SpawnLocation, FVector& ShootingForce)
{
	Bullet.MeshRoot->SetPhysicsLinearVelocity(FVector(0));	// Ensures that velocity is 0 so bullets can't end up at terminal velocity when spawning

	Bullet.SetActorLocation(SpawnLocation);
	
	Bullet.SetActorRotation(ShootingForce.Rotation());	// Sets Bullet Location and Rotation

	// Casts the root of the bullet actor to static mesh comp
	Bullet.MeshRoot->SetSimulatePhysics(true);
	Bullet.MeshRoot->SetVisibility(true);	// Starts simulating physics and makes bullets visible

	ShootingForce *= BlackboardComp->GetValueAsFloat("BulletSpeed");

	Bullet.MeshRoot->AddImpulse(ShootingForce);	// Shoots Bullet with Impulse

	Bullet.BulletTime = BlackboardComp->GetValueAsFloat("BulletLife");
	Bullet.BulletTimer = Bullet.BulletTime;	// Starts bullet despawn timer and goes to next bullet

	GunFireComp->Play();	// Plays Gun fire sound
}

void ACustomAIController::BulletLogic(const FVector& SpawnLocation, const FVector& TraceDir, const float& BulletDamage)
{
	FHitResult hit = FHitResult();	// intializes hit var

	/*GetWorld()->DebugDrawTraceTag = "DebugLine";

	FCollisionQueryParams params;
	params.TraceTag = GetWorld()->DebugDrawTraceTag;*/

	FVector TraceVector = TraceDir * BlackboardComp->GetValueAsFloat("BulletDist");
	
	GetWorld()->LineTraceSingleByChannel(hit, SpawnLocation, SpawnLocation + TraceVector, ECollisionChannel::ECC_Pawn);

	if (AStealthAICharacter* Player = Cast<AStealthAICharacter>(hit.GetActor()))
	{
		Player->Health -= BulletDamage;
	}
}