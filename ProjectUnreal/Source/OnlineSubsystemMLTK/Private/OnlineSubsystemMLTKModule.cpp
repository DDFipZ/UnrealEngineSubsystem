#include "OnlineSubsystemMLTKModule.h"
#include "OnlineSubsystemMLTK.h"
#include "OnlineSubsystem.h"


#define LOCTEXT_NAMESPACE "FOnlineSubsystemMLTKModule"
IMPLEMENT_MODULE(FOnlineSubsystemMLTKModule, MLTK_ONLINESUBSYSTEM)

class FOnlineSubsystemMLTKFactory : public IOnlineFactory
{
public:
	FOnlineSubsystemMLTKFactory() {}
	virtual ~FOnlineSubsystemMLTKFactory() {}

	static FOnlineSubsystemMLTKPtr OnlineSubsystemMLTKSingleton;

	virtual IOnlineSubsystemPtr CreateSubsystem(FName InstanceName)
	{
		OnlineSubsystemMLTKSingleton = MakeShared<FOnlineSubsystemMLTK, ESPMode::ThreadSafe>(InstanceName);
		if (OnlineSubsystemMLTKSingleton->IsEnabled())
		{
			if(!OnlineSubsystemMLTKSingleton->Init())
			{
				UE_LOG_ONLINE(Warning, TEXT("MLTK API failed to initialize!"));
				OnlineSubsystemMLTKSingleton->Shutdown();
				OnlineSubsystemMLTKSingleton = NULL;
			}
		}
		else
		{
			UE_LOG_ONLINE(Warning, TEXT("MLTK API disabled!"));
			OnlineSubsystemMLTKSingleton->Shutdown();
			OnlineSubsystemMLTKSingleton = NULL;
		}
	
		return OnlineSubsystemMLTKSingleton;
	}
};

FOnlineSubsystemMLTKPtr FOnlineSubsystemMLTKFactory::OnlineSubsystemMLTKSingleton = nullptr;

void FOnlineSubsystemMLTKModule::StartupModule()
{
	FactoryMLTK = new FOnlineSubsystemMLTKFactory();

	// Create and register our singleton factory with the main online subsystem for easy access
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.RegisterPlatformService(MLTK_ONLINESUBSYSTEM, FactoryMLTK);
}

void FOnlineSubsystemMLTKModule::ShutdownModule()
{
	FOnlineSubsystemModule& OSS = FModuleManager::GetModuleChecked<FOnlineSubsystemModule>("OnlineSubsystem");
	OSS.UnregisterPlatformService(MLTK_ONLINESUBSYSTEM);
	
	delete FactoryMLTK;
	FactoryMLTK = NULL;
}

void FOnlineSubsystemMLTKModule::DeleteFactory()
{
	if (FOnlineSubsystemMLTKFactory::OnlineSubsystemMLTKSingleton.IsValid())
	{
		FOnlineSubsystemMLTKFactory::OnlineSubsystemMLTKSingleton->Shutdown();
		FOnlineSubsystemMLTKFactory::OnlineSubsystemMLTKSingleton.Reset();
	}
	
	delete FactoryMLTK;
	FactoryMLTK = NULL;
}

#undef LOCTEXT_NAMESPACE
    
