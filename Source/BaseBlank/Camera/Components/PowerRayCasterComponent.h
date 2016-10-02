

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
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers Management")
    float FloorTraceLenght = 9999.f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Powers Management")
    TEnumAsByte<ECollisionChannel> FloorRayTraceChannel = ECollisionChannel::ECC_Visibility;
    
    UPROPERTY(EditDefaultsOnly, Category = "Powers Management")
    TArray<TSubclassOf<ABasePowerActor>> PowersClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "Powers Management")
    int32 StartWithSelectedPowerIndex = 0;
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    void SelectNextPower();
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    void SelectPreviousPower();
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    void SelectPower(int32 _power);
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    void UsePower();
    
	//Can be null if now power is selected (and that can happen if there are no usable powers)
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    ABasePowerActor * GetActivePower();
    
    UFUNCTION(BlueprintCallable, Category="JD|Powers Management")
    int32 GetCurrentPowerIndex();

	UFUNCTION(BlueprintCallable, Category = "JD|Powers Management")
	FString GetCurrentPowerName();
    
    UPROPERTY(BlueprintReadOnly, Category = "Powers Management")
    TArray<class ABasePowerActor *> Powers;
    
    virtual void OnRegister() override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "JD|Powers Management")
	void SelectNextUsablePower();

	UFUNCTION(BlueprintCallable, Category = "JD|Powers Management")
	void SelectPrevUsablePower(); 

	UFUNCTION(BlueprintCallable, Category = "JD|Powers Management")
	void UpdateUsablePowers();

	//Set the postion of the currently active power
	UFUNCTION(BlueprintCallable, Category = "JD|Powers Management")
	void SetActivePowerPosition(FVector Position, FRotator Rotation);

	void OnGameModeSoulsChange(float oldSouls, float newSouls);

	//Enable raycast from player camera to terrain channel
	UPROPERTY(EditDefaultsOnly, Category = "Powers Management")
	bool bEnablePowerRaycast;
    
private:
    
    ABasePowerActor * m_activePower;
    
    int32 m_currentPowerIndex = 0;
    
    void DoPowerRaycast();
};
