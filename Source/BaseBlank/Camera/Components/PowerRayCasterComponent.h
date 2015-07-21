

#pragma once

#include "Components/ActorComponent.h"
#include "Powers/BasePowerActor.h"
#include "PowerRayCasterComponent.generated.h"


/**
 * 
 */
UCLASS(ClassGroup = (Logic, Common), editinlinenew, meta = (BlueprintSpawnableComponent),BlueprintType)
class BASEBLANK_API UPowerRayCasterComponent : public UActorComponent
{
	GENERATED_BODY()
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float FloorTraceLenght = 9999.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TEnumAsByte<ECollisionChannel> FloorRayTraceChannel = ECollisionChannel::ECC_Visibility;
    
    UPROPERTY(EditDefaultsOnly)
    TArray<TSubclassOf<ABasePowerActor>> PowersClass;
    
    UPROPERTY(EditDefaultsOnly)
    int32 StartWithSelectedPowerIndex = 0;
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    void SelectNextPower();
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    void SelectPreviousPower();
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    void SelectPower(int32 _power);
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    void UsePower();
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    ABasePowerActor * GetActivePower();
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    int32 GetCurrentPowerIndex();
    
    UPROPERTY(BlueprintReadOnly)
    TArray<class ABasePowerActor *> Powers;
    
    virtual void OnRegister() override;
    
private:
    
    ABasePowerActor * m_activePower;
    
    int32 m_currentPowerIndex = 0;
    
    void DoPowerRaycast();
};
