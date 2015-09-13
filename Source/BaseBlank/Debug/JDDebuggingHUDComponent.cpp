#include "BaseBlank.h"
#include "JDDebuggingComponent.h"
#include "Global/BaseBlankGameMode.h"
#include "NPCController/NPCController.h"
#include "NPCController/Components/BehaviourComponent.h"
#include "Character/Components/EffectComponent.h"
#include "Character/Effects/BaseEffect.h"
#include "Character/Effects/BaseEffect.h"
#include "JDDebuggingHUDComponent.h"




void AJDDebuggingHUDComponent::DrawGameSpecificView(APlayerController* PC, class UGameplayDebuggingComponent *DebugComponent)
{
	Super::DrawGameSpecificView(PC, DebugComponent);

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if (DebugComponent && GameplayDebuggerSettings(GetDebuggingReplicator()).CheckFlag(EAIDebugDrawDataView::GameView1))
	{
		PrintString(DefaultContext, FColor::Green, TEXT("\nJD DEBUG\n"));

		const UJDDebuggingComponent* MyComp = Cast<UJDDebuggingComponent>(DebugComponent);

		if (MyComp)
		{

			const TArray<UBaseEffect *> activeEffects = MyComp->JDGameMode->GetActiveEffects();

			FString effectName;
			if (activeEffects.Num() > 0)
			{
				PrintString(DefaultContext, FString::Printf(TEXT("{white}All active effects are :\n")));

				for (const UBaseEffect * effect : activeEffects)
				{
					effect->GetName(effectName);
					PrintString(DefaultContext, FString::Printf(TEXT("  {green}%s\n"), *effectName));
				}
			}



			TArray<ANPCController *> & npcs = MyComp->JDGameMode->GetNPCs();

			for (ANPCController * npc : npcs)
			{

				ENPCBehaviour behavior = npc->BehaviourComponent->GetNPCBehaviour();

				FString behaviorName;
				const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ENPCBehaviour"), true);
				if (!EnumPtr)
				{
					behaviorName = FString("Invalid");
				}

				behaviorName = EnumPtr->GetEnumName((int32)behavior);

				FString name = "";
				npc->GetName(name);


				PrintString(DefaultContext, FString::Printf(TEXT("{white}NPC {green}%s {white}has behaviour {green}%s\n"), *name, *behaviorName));

				ABaseCharacter * baseCharacter = Cast<ABaseCharacter>(npc->GetControlledPawn());


				for (UBaseEffect * effect : baseCharacter->PowerInteractionsComponent->Effects)
				{
					effect->GetName(effectName);
					PrintString(DefaultContext, FString::Printf(TEXT("  {white}Effect {green}%s\n"), *effectName));
				}

				
			}


		}

	}
#endif

}

void AJDDebuggingHUDComponent::GetKeyboardDesc(TArray<FDebugCategoryView>& Categories)
{
	Super::GetKeyboardDesc(Categories);

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	Categories.Add(FDebugCategoryView(EAIDebugDrawDataView::GameView1, TEXT("JD Debug")));
#endif

}