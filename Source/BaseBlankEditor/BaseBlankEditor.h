// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "ModuleManager.h"
#include "SharedPointer.h"
#include "AssetToolsModule.h"

class EditorModule : public IModuleInterface
{
    virtual void StartupModule() override;
    
    virtual void ShutdownModule() override;

};
