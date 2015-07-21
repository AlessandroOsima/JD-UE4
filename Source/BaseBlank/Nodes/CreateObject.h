

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "CreateObject.generated.h"

/**
 * 
 */
UCLASS()
class BASEBLANK_API UCreateObject : public UEdGraphNode
{
	GENERATED_BODY()
	

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Create Object From Blueprint", CompactNodeTitle = "Create", Keywords = "new create blueprint"), Category = Game)
	static UObject * CreateObject(TSubclassOf<UObject> UC);
	
	
};
