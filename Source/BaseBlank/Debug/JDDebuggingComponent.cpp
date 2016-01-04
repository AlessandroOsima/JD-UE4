#include "BaseBlank.h"
#include "GameplayDebuggingComponent.h"
#include "UnrealNetwork.h"
#include "JDDebuggingComponent.h"

void UJDDebuggingComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	DOREPLIFETIME(UJDDebuggingComponent, JDGameMode);
#endif
}

void UJDDebuggingComponent::CollectDataToReplicate(bool bCollectExtendedData)
{
	Super::CollectDataToReplicate(bCollectExtendedData);

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if (ShouldReplicateData(EAIDebugDrawDataView::GameView1))
	{

		JDGameMode = Cast<ABaseBlankGameMode>(GetWorld()->GetAuthGameMode());
		
		UWorld* World = GetWorld();

		for (TActorIterator<ACameraPawn> It(World); It; ++It)
		{
			JDCameraPawns.Add(*It);
		}

		if (bCollectExtendedData)
		{
			// collect additional data for selected Pawn/AIController 
		}
	}
#endif
}