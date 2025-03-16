#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#ifndef MLTK_ONLINESUBSYSTEM
const FName MLTK_ONLINESUBSYSTEM = TEXT("OnlineSubsystemMLTK");
#endif

class FOnlineSubsystemMLTKModule : public IModuleInterface
{
private:
    class FOnlineSubsystemMLTKFactory* FactoryMLTK;

public:

    FOnlineSubsystemMLTKModule() :
        FactoryMLTK(NULL) {}

    virtual ~FOnlineSubsystemMLTKModule() {}
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    void DeleteFactory();
    virtual bool SupportsDynamicReloading() override
    {
        return false;
    }

    virtual bool SupportsAutomaticShutdown() override
    {
        return false;
    }
};
