

#include "BaseBlank.h"
#include "CharPowerInteractionsComponent.h"
#include "Character/BaseCharacter.h"
#include "NPCController/NPCController.h"
#include "NPCController/Components/BehaviourComponent.h"




void UCharPowerInteractionsComponent::OnRegister()
{
	Super::OnRegister();

	ensureMsgf(GetOwner() && Cast<ABaseCharacter>(GetOwner()), TEXT("Owner Must be or derive from ABaseCharacter"));
}

void UCharPowerInteractionsComponent::BeginPlay()
{
	Super::BeginPlay();

	ABaseCharacter * owner = Cast<ABaseCharacter>(GetOwner());

	UBehaviourComponent * behaviour = (UBehaviourComponent *)owner->GetController()->GetComponentByClass(UBehaviourComponent::StaticClass());

	if (behaviour)
	{
		behaviour->RegisterObserver(this, FOnBehaviorChangeDelegate::CreateUObject(this, &UCharPowerInteractionsComponent::OnCharacterStateChange));
	}
}

void UCharPowerInteractionsComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//Because controller is destroyed before this component the callback array has already being removed and we do not need to unregister from it
	/*ABaseCharacter * owner = Cast<ABaseCharacter>(GetOwner());

	UBehaviourComponent * behaviour = (UBehaviourComponent *)owner->GetController()->GetComponentByClass(UBehaviourComponent::StaticClass());

	if (behaviour)
	{
		behaviour->UnRegisterObserver(this);
	}*/
}

void UCharPowerInteractionsComponent::OnCharacterStateChange(ABaseCharacter * Character, ENPCBehaviour OldBehavior, ENPCBehaviour NewBehavior)
{
	if (NewBehavior != OldBehavior && NewBehavior == ENPCBehaviour::Dead)
	{
		this->Deactivate();
	}
	else if (NewBehavior != OldBehavior && NewBehavior != ENPCBehaviour::Dead && !this->IsActive())
	{
		this->Activate();
	}
}

