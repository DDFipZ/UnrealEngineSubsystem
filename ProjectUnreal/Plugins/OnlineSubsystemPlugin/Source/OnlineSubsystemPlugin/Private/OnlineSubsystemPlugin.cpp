// Copyright Epic Games, Inc. All Rights Reserved.

#include "OnlineSubsystemPlugin.h"
#include "OnlineSubsystemMLTK.h"

#define LOCTEXT_NAMESPACE "FOnlineSubsystemPluginModule"
IMPLEMENT_MODULE(FOnlineSubsystemPluginModule, MLTK_ONLINESUBSYSTEM)
class FOnlineSubsystemMLTKFactory : public IOnlineFactory
{
public:
	FOnlineSubsystemMLTKFactory() {}
	virtual ~FOnlineSubsystemMLTKFactory() override {}

	static FOnlineSubsystemMLTKPtr OnlineSubsystemMLTKSingleton;

	virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName) override
	{	
		OnlineSubsystemMLTKSingleton = MakeShared<FOnlineSubsystemMLTK, ESPMode::ThreadSafe>(InstanceName);
		if (OnlineSubsystemMLTKSingleton->IsEnabled())
		{
			if(!OnlineSubsystemMLTKSingleton->Init())
			{
				UE_LOG_ONLINE(Warning, TEXT("MLTK API failed to initialize!"));
				OnlineSubsystemMLTKSingleton->Shutdown();
				OnlineSubsystemMLTKSingleton = nullptr;
			}
		}
		else
		{
			UE_LOG_ONLINE(Warning, TEXT("MLTK API disabled!"));
			OnlineSubsystemMLTKSingleton->Shutdown();
			OnlineSubsystemMLTKSingleton = nullptr;
		}
	
		return OnlineSubsystemMLTKSingleton;
	}
};

FOnlineSubsystemMLTKPtr FOnlineSubsystemMLTKFactory::OnlineSubsystemMLTKSingleton = nullptr;

void FOnlineSubsystemPluginModule::DeleteFactory()
{
	if (FOnlineSubsystemMLTKFactory::OnlineSubsystemMLTKSingleton.IsValid())
	{
		FOnlineSubsystemMLTKFactory::OnlineSubsystemMLTKSingleton->Shutdown();
		FOnlineSubsystemMLTKFactory::OnlineSubsystemMLTKSingleton.Reset();
	}
	
	delete FactoryMLTK;
	FactoryMLTK = nullptr;
}

void FOnlineSubsystemPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FactoryMLTK = new FOnlineSubsystemMLTKFactory();

	if (FModuleManager::Get().IsModuleLoaded("OnlineSubsystem"))
	{
		UE_LOG_ONLINE(Warning, TEXT("Checking for online subsystem"));
		// Create and register our singleton factory with the main online subsystem for easy access
		FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
		OSS.RegisterPlatformService(MLTK_ONLINESUBSYSTEM, FactoryMLTK);
	}
	else
	{
		UE_LOG_ONLINE(Warning, TEXT("Online subsystem is not initialzed!"));
	}
}

void FOnlineSubsystemPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.UnregisterPlatformService(MLTK_ONLINESUBSYSTEM);
	
	delete FactoryMLTK;
	FactoryMLTK = nullptr;
}


#undef LOCTEXT_NAMESPACE