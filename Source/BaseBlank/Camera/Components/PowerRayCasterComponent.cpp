

#include "BaseBlank.h"
#include "Array.h"
#include "PowerRayCasterComponent.h"




void UPowerRayCasterComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    if(m_activePower != nullptr)
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
    
    FCollisionQueryParams parm(FName(TEXT("JD Trace")),true);
    
    FHitResult res;
    
    if(GetWorld()->LineTraceSingle(res, location, endLocation, FloorRayTraceChannel.GetValue(), parm))
    {
        color = FColor::Green;
        
        DrawDebugSolidBox(GetWorld(), res.ImpactPoint, FVector(15, 15, 15), FColor::Green);
        m_activePower->GetTransform().SetLocation(res.ImpactPoint);
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
    
    for(int i = 0; i < PowersClass.Num(); i++)
    {
        UClass * targetClass = *PowersClass[i];
        
        Powers.Add(GetWorld()->SpawnActor<ABasePowerActor>(targetClass,
                                                           this->GetOwner()->GetTransform().GetLocation(),
                                                           this->GetOwner()->GetTransform().Rotator()));
    }
    
    SelectPower(StartWithSelectedPowerIndex);
}

void UPowerRayCasterComponent::SelectNextPower()
{
    int32 next = m_currentPowerIndex + 1;
    if(next >= Powers.Num())
    {
        next = 0;
    }
    
    SelectPower(next);
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
    int32 prev = m_currentPowerIndex - 1;
    if(prev < 0)
    {
        prev = Powers.Num() - 1;
    }
    
    SelectPower(prev);
}

void UPowerRayCasterComponent::SelectPower(int32 _power)
{
    if(Powers.Num() > 0 && Powers.Num() > _power)
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