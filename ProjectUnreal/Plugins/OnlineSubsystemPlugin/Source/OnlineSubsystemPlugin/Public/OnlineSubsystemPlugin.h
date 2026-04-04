// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"
#ifndef MLTK_ONLINESUBSYSTEM
const FName MLTK_ONLINESUBSYSTEM = TEXT("OnlineSubsystemPlugin");
#endif
class FOnlineSubsystemPluginModule : public IModuleInterface
{
public:

private:
	class FOnlineSubsystemMLTKFactory* FactoryMLTK;
public:
	FOnlineSubsystemPluginModule() :
		FactoryMLTK(NULL) {}
	virtual ~FOnlineSubsystemPluginModule() {}
	void DeleteFactory();
	virtual bool SupportsDynamicReloading() override
	{
		return false;
	}

	virtual bool SupportsAutomaticShutdown() override
	{
		return false;
	}
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
