#include "UWebSocketAccessor.h"

UWebSocketAccessor::UWebSocketAccessor()
{
	UE_LOG(LogTemp, Display, TEXT("Create Socket Accessor"));
}

bool UWebSocketAccessor::Init(FString SessionId, FString WebserviceUrl)
{
	if (LibraryWrapper == nullptr)
		LibraryWrapper = std::make_shared<OnlineSubsystemPluginLibraryWrapper>();
	
	std::string sessionIdStr = std::string(TCHAR_TO_UTF8(*SessionId));
	std::string webserviceUrlStr = std::string(TCHAR_TO_UTF8(*WebserviceUrl));
	
	LibraryWrapper->init(sessionIdStr, webserviceUrlStr);
	return true;
}
