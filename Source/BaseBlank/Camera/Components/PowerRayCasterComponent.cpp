

#include "BaseBlank.h"
#include "Array.h"
#include "PowerRayCasterComponent.h"
#include "Global/GameModeInfo/FreeGameMode/FreeModeSoulsInfoComponent.h"




void UPowerRayCasterComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    if(m_activePower != nullptr && bEnablePowerRaycast)
    {
        //UE_LOG(LogTemp, Log, TEXT("Power index is %d"),m_currentPowerIndex);
        DoPowerRaycast();
    }
}

void UPowerRayCasterComponent::DoPowerRaycast()
{
    APawn * camPawn = Cast<APawn>(this->GetOwner());
    
    FVector direction = camPawn->GetControlRotation().Vector();
    
    FVector location = this->GetOwner()->GetTransform().GetLocation();
    FVector endLocation = location + direction * FloorTraceLenght;
    
    FColor color = FColor::Red;
    
	FCollisionObjectQueryParams params;
	params.AddObjectTypesToQuery(FloorRayTraceChannel);

    FHitResult res;
    
    if(m_activePower != nullptr && GetWorld()->LineTraceSingleByObjectType(res, location, endLocation, params))
    {
        color = FColor::Green;
        
		m_activePower->SetActorLocation(res.ImpactPoint);

		FColor boxColor = FColor::Green;

		if (!m_activePower->CanUse())
		{
			boxColor = FColor::Red;
		}

		//DrawDebugSolidBox(GetWorld(), res.ImpactPoint, FVector(15, 15, 15), boxColor);
    }
	
    DrawDebugLine(GetWorld(), location, endLocation, color);
    
    DrawDebugLine(GetWorld(), location, location + FVector::UpVector * 10, FColor::Black);
    DrawDebugLine(GetWorld(), endLocation, endLocation + FVector::UpVector * 10, FColor::Blue);
    
    DrawDebugLine(GetWorld(), location, location + direction * 10, FColor::Magenta);
}

ABasePowerActor * UPowerRayCasterComponent::GetActivePower()
{
    return m_activePower;
}

void UPowerRayCasterComponent::OnRegister()
{
    Super::OnRegister();

	for (int i = 0; i < PowersClass.Num(); i++)
	{
		UClass * targetClass = *PowersClass[i];

		Powers.Add(GetWorld()->SpawnActor<ABasePowerActor>(targetClass,
			this->GetOwner()->GetTransform().GetLocation(),
			this->GetOwner()->GetTransform().Rotator()));
	}

	
}

void UPowerRayCasterComponent::BeginPlay()
{
	Super::BeginPlay();

	SelectPower(StartWithSelectedPowerIndex);

	//Register to game mode souls info component
	AGameMode * gm = GetWorld()->GetAuthGameMode();

	UFreeModeSoulsInfoComponent * cmp = Cast<UFreeModeSoulsInfoComponent>(gm->GetComponentByClass(UFreeModeSoulsInfoComponent::StaticClass()));

	ensure(cmp);

	if (cmp)
	{
		cmp->OnSoulsChange().AddUObject(this, &UPowerRayCasterComponent::OnGameModeSoulsChange);
	}

}

void UPowerRayCasterComponent::SelectNextUsablePower()
{
	int32 currentIndex = m_currentPowerIndex + 1;
	bool found = false;

	while (currentIndex != m_currentPowerIndex)
	{
		if (currentIndex >= Powers.Num())
		{
			currentIndex = 0;
		}

		if (Powers[currentIndex]->HasEnoughSoulsToSpend())
		{
			SelectPower(currentIndex);
			found = true;
			break;
		}

		currentIndex++;

	}

	if (!found && m_activePower && !m_activePower->HasEnoughSoulsToSpend())
	{
		m_activePower = nullptr;
		m_currentPowerIndex = 0;
	}
}

void UPowerRayCasterComponent::SelectPrevUsablePower()
{
	int32 currentIndex = m_currentPowerIndex - 1;
	bool found = false;

	while (currentIndex != m_currentPowerIndex)
	{
		if (currentIndex < 0)
		{
			currentIndex = Powers.Num() - 1;
		}

		if (Powers[currentIndex]->HasEnoughSoulsToSpend())
		{
			SelectPower(currentIndex);
			found = true;
			break;
		}

		currentIndex--;

	}

	if (!found && m_activePower && !m_activePower->HasEnoughSoulsToSpend())
	{
		m_activePower = nullptr;
	}
}

void UPowerRayCasterComponent::UpdateUsablePowers()
{
	if (m_activePower && !m_activePower->HasEnoughSoulsToSpend())
	{
		SelectNextUsablePower();
	}
	else if (!m_activePower)
	{
		//Try to restore the prev selected
		if (Powers[m_currentPowerIndex]->HasEnoughSoulsToSpend())
		{
			SelectPower(m_currentPowerIndex);
		}
		
		SelectNextUsablePower();
	}
}

void UPowerRayCasterComponent::SetActivePowerPosition(FVector Position, FRotator Rotation)
{
	if (m_activePower != nullptr)
	{
		m_activePower->SetActorLocation(Position);
		m_activePower->SetActorRotation(Rotation.Quaternion());

		FColor boxColor = FColor::Green;
	}
}

void UPowerRayCasterComponent::OnGameModeSoulsChange(float OldSouls, float NewSouls)
{
	UpdateUsablePowers();
}

void UPowerRayCasterComponent::SelectNextPower()
{
	SelectNextUsablePower();
}

void UPowerRayCasterComponent::UsePower()
{
    if(m_activePower != nullptr)
    {
        if(m_activePower->CanUse())
        {
            m_activePower->Use();
        }
    }
}


void UPowerRayCasterComponent::SelectPreviousPower()
{
	SelectPrevUsablePower();
}

void UPowerRayCasterComponent::SelectPower(int32 _power)
{
	if (Powers.Num() > 0 && Powers.Num() > _power && Powers[_power]->HasEnoughSoulsToSpend())
    {
        if(m_activePower != nullptr)
        {
            m_activePower->SetActorHiddenInGame(true);
            m_activePower->UnSelecting();
        }
        
        m_activePower = Powers[_power];
        
        m_activePower->SetActorHiddenInGame(false);
        m_activePower->Selecting();
        
        m_currentPowerIndex = _power;
    }
}

int32 UPowerRayCasterComponent::GetCurrentPowerIndex()
{
    return m_currentPowerIndex;
}

FString UPowerRayCasterComponent::GetCurrentPowerName()
{
	FString powerName = "";

	if (GetActivePower())
	{
		powerName = GetActivePower()->Name;
	}

	return powerName;
}
