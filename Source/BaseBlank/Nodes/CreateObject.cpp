

#include "BaseBlank.h"
#include "CreateObject.h"




UObject * UCreateObject::CreateObject(TSubclassOf<UObject> UC)
{
	return  StaticConstructObject(UC);
}