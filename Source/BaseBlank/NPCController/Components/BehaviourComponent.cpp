// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBlank.h"
#include "BehaviourComponent.h"
#include "Character/BaseCharacter.h"
#include "Character/Components/LifeComponent.h"
#include "Global/BaseBlankGameMode.h"
#include "Global/GameModeInfo/FreeGameMode/FreeModeSoulsInfoComponent.h"
#include "Character/Configuration/CharacterConfigurationAsset.h"


UBehaviourComponent::UBehaviourComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UBehaviourComponent::BeginPlay()
{
	//This is initialization, we do not want to notify observers since CurrentBehavior is set to default invalid state until after this call
	ComputeNPCBehaviour(false);

	LifeChangeDelegate = m_targetNPC->LifeComponent->OnLifeChange().AddUObject(this, &UBehaviourComponent::OnLifeValueChange);
}

void UBehaviourComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//ComputeNPCBehaviour();
}


void UBehaviourComponent::SetTargetNPC(ABaseCharacter * _targetNPC)
{
    check(_targetNPC)
    
    m_targetNPC = _targetNPC;
}

ENPCBehaviour UBehaviourComponent::GetNPCBehaviour()
{
	return CurrentBehavior;
}

void UBehaviourComponent::ComputeNPCBehaviour(bool DoNotifyObservers)
{

	ENPCBehaviour oldBehaviour = CurrentBehavior;

	if (m_targetNPC != nullptr)
	{
		ULifeComponent * life = m_targetNPC->LifeComponent;

		if (life != nullptr)
		{
			if (life->GetLife() > 0)
			{
				if (life->GetLife() > life->GetMaxLife() / 2)
				{
					CurrentBehavior = ENPCBehaviour::Normal;
				}
				else
				{
					CurrentBehavior = ENPCBehaviour::Injured;
				}
			}
			else
			{
				if (CurrentBehavior != ENPCBehaviour::Dead)
				{
					CurrentBehavior = ENPCBehaviour::Dead;

					ABaseBlankGameMode * gameMode = Cast<ABaseBlankGameMode>(m_targetNPC->GetWorld()->GetAuthGameMode());
					ensure(gameMode);

					UFreeModeSoulsInfoComponent * cmp = Cast<UFreeModeSoulsInfoComponent>(gameMode->FindComponentByClass(UFreeModeSoulsInfoComponent::StaticClass()));
					ensureMsgf(gameMode, TEXT("Current game mode has no UFreeModeSoulsInfoComponent"));

					cmp->UseSoulsAmount(-m_targetNPC->Configuration->SoulsOnDeath);

				}
			}

			if (DoNotifyObservers && CurrentBehavior != oldBehaviour)
			{
				NotifyObservers(oldBehaviour, CurrentBehavior);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("[UBehaviourComponent]No life component found"))
		}

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[UBehaviourComponent]Target NPC is null"))
	}

}

void UBehaviourComponent::RegisterObserver(UObject * Owner, FOnBehaviorChangeDelegate Observer)
{
	ensure(Owner);

	if (!Observers.Contains(Owner))
	{
		Observers.Add(Owner, Observer);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("[BehaviorComponent] Unable to register another observer with the same owner"));
	}
	
}

void UBehaviourComponent::UnRegisterObserver(UObject * Owner)
{
	ensure(Owner);

	if (!Observers.Contains(Owner))
	{
		UE_LOG(LogTemp, Error, TEXT("[BehaviorComponent] No observers registered with this owner"));
	}
	else
	{
		Observers.Remove(Owner);
	}
}

void UBehaviourComponent::NotifyObservers(ENPCBehaviour OldBehavior, ENPCBehaviour NewBehavior)
{
	if (Observers.Num() == 0)
	{
		return;
	}
		

	for (auto it = Observers.CreateIterator(); it; ++it)
	{
		FOnBehaviorChangeDelegate & value =  it.Value();

		value.ExecuteIfBound(m_targetNPC, OldBehavior, NewBehavior);
	}
}

void UBehaviourComponent::OnLifeValueChange(ABaseCharacter * Owner, float OldBehavior, float NewBehavior)
{
	ComputeNPCBehaviour();
}

void UBehaviourComponent::OnUnregister()
{
	Super::OnUnregister();

	if (m_targetNPC)
	{
		m_targetNPC->LifeComponent->OnLifeChange().Remove(LifeChangeDelegate);
	}
}

