//
//  AssetTypeActions_CharConfig.h
//  BaseBlank
//
//  Created by Alessandro Osima on 03/11/14.
//  Copyright (c) 2014 EpicGames. All rights reserved.
//

#pragma once
#include "Character/Configuration/CharacterConfigurationAsset.h"

//Necessary to compile public FAssetTypeActions_Base
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "EditorStyle.h"
#include "Editor/UnrealEd/Classes/Settings/EditorLoadingSavingSettings.h"
//

#include "AssetTypeActions_Base.h"

class FAssetTypeActions_CharConfig : public FAssetTypeActions_Base
{
public:
    // IAssetTypeActions Implementation
    virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_CharConfig", "Character Configuration"); }
    virtual FColor GetTypeColor() const override { return FColor(201, 29, 85); }
    virtual UClass* GetSupportedClass() const override { return UCharacterConfigurationAsset::StaticClass(); }
    virtual uint32 GetCategories() override { return EAssetTypeCategories::Gameplay; }
};