// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "NPCController.h"
#include "Character/BaseCharacter.h"

NPCControllerBlackBoardKeys ANPCController::BlackboardKeys = NPCControllerBlackBoardKeys();

ANPCController::ANPCController(const class FObjectInitializer& PCIP)
	: Super(PCIP.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
    BHTComponent = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComponent"));
    BlackboardComponent = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
    BehaviourComponent = PCIP.CreateDefaultSubobject<UBehaviourComponent>(this, TEXT("BehaviourComponent"));
	TargetComponent = PCIP.CreateDefaultSubobject<UIndicatorTargetComponent>(this, TEXT("TargetComponent"));
}

void ANPCController::BeginPlay()
{
    Super::BeginPlay();


	//Detour crowds
	UCrowdFollowingComponent * ccmp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());

	ensure(ccmp);

	ccmp->SetCrowdAnticipateTurns(true);
	ccmp->SetCrowdPathOffset(true);
	ccmp->SetCrowdCollisionQueryRange(600);
	ccmp->SetCrowdPathOptimizationRange(1500.f);
	ccmp->SetCrowdSeparation(true);
	ccmp->SetCrowdSeparationWeight(5.0f);
	ccmp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
	//ccmp->SetCrowdAvoidanceRangeMultiplier(2.0f);
    ///

	ensureMsgf(BHTAsset != nullptr, TEXT("[BaseCharacter]No bht asset found"));
    
    BlackboardComponent->InitializeBlackboard(*BlackboardAsset);
    
    
    BHTComponent->StartTree(*BHTAsset);
    BHTComponent->PrimaryComponentTick.bCanEverTick = true;
    
    SetupBlackboardKeys();
    
}

void ANPCController::SetupBlackboardKeys()
{
    //Setup blk keys here
    ABaseCharacter * toPossess = Cast<ABaseCharacter>(GetPawn());
    
    if(toPossess)
    {
        BlackboardComponent->SetValueAsObject(ANPCController::BlackboardKeys.TargetActor, toPossess);
        BlackboardComponent->SetValueAsInt(ANPCController::BlackboardKeys.TargetIndex, 0);
    }
}

void ANPCController::PushNewBHTAsset(UBehaviorTree* BHTAssetToLoad)
{
	ensureMsgf(BHTAssetToLoad != nullptr, TEXT("BHT Asset does not exist"));

	BHTComponent->StartTree(*BHTAssetToLoad);

	SetupBlackboardKeys();
}

ABaseCharacter * ANPCController::GetBaseCharacter()
{
	ensure(this->GetPawn());

	return Cast<ABaseCharacter>(this->GetPawn());
}

void ANPCController::PopBHTAsset()
{
	BHTComponent->StartTree(*BHTAsset);
}

void ANPCController::Tick(float _deltaTime)
{
    ABaseCharacter * BaseChr = Cast<ABaseCharacter>(BlackboardComponent->GetValueAsObject(ANPCController::BlackboardKeys.TargetActor));
}

void ANPCController::Possess(APawn *_pawn)
{
    Super::Possess(_pawn);
    
    ABaseCharacter * BaseChr = Cast<ABaseCharacter>(_pawn);
    
    if(BaseChr != nullptr)
    {
        BlackboardComponent->SetValueAsObject(ANPCController::BlackboardKeys.TargetActor, BaseChr);
        BehaviourComponent->SetTargetNPC(BaseChr);
    }
    else
    {
		ensureMsgf(0, TEXT("[ANPCController]Possessing a non BaseCharacter Pawn, that doesn't sound good"));
    }
}

