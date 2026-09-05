#pragma once
#include "OnlineSubsystemPluginLibraryWrapper.h"
#include "UWebSocketAccessor.generated.h"

class OnlineSubsystemPluginLibraryWrapper;

UCLASS()
class ONLINESUBSYSTEMPLUGIN_API UWebSocketAccessor: public UObject
{
	GENERATED_BODY()
public:
	std::shared_ptr<OnlineSubsystemPluginLibraryWrapper> LibraryWrapper;
	UWebSocketAccessor();
	bool Init(FString SessionId, FString WebserviceUrl);
};
