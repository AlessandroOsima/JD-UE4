// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "NPCController.h"
#include "Character/BaseCharacter.h"

NPCControllerBlackBoardKeys ANPCController::BlackboardKeys = NPCControllerBlackBoardKeys();

ANPCController::ANPCController(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
    BHTComponent = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComponent"));
    BlackboardComponent = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
    BehaviourComponent = PCIP.CreateDefaultSubobject<UBehaviourComponent>(this, TEXT("BehaviourCOmponent"));
}

void ANPCController::BeginPlay()
{
    Super::BeginPlay();
    
    ensureMsg(BHTAsset != nullptr,TEXT("[BaseCharacter]No bht asset found"));
    
    BlackboardComponent->InitializeBlackboard(BlackboardAsset);
    
    
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
        UE_LOG(LogTemp, Warning, TEXT("[ANPCController]Possessing a non BaseCharacter Pawn, that doesn't sound good"));
    }
}

