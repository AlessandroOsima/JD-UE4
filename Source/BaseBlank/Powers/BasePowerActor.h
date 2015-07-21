

#pragma once

#include "GameFramework/Actor.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Engine/Texture2D.h"
#include "UMG.h"
#include "UI/PowerWidget.h"
#include "BasePowerActor.generated.h"


class UPowerConfigurationAsset;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BASEBLANK_API ABasePowerActor : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Info")
    int32 SoulsCost;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Info")
    FString Name;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Power Info")
    FString Description;
    
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UBehaviorTree * BHTAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UPowerWidget> PowerWidget;
   
public:

	UFUNCTION(BlueprintNativeEvent, Category = "JD, Powers")
	bool CanUse();
    
	UFUNCTION(BlueprintNativeEvent, Category = "JD, Powers")
	void Use();
    
	UFUNCTION(BlueprintNativeEvent, Category = "JD, Powers")
	void Selecting();
    
	UFUNCTION(BlueprintNativeEvent, Category = "JD, Powers")
	void UnSelecting();    

	UFUNCTION(BlueprintCallable, Category = "JD, Powers")
	void SpendSouls();

	UFUNCTION(BlueprintCallable, Category = "JD, Powers")
	bool CanSpendWithoutLosing();

	
};

