#include "OnlineSubsystemMLTK.h"

#include "OnlineSessionInterfaceMLTK.h"
#include "OnlineSessionSettings.h"

IOnlineSessionPtr FOnlineSubsystemMLTK::GetSessionInterface() const
{
	return SessionInterface;
}

IOnlineFriendsPtr FOnlineSubsystemMLTK::GetFriendsInterface() const
{
	return nullptr;
}

bool FOnlineSubsystemMLTK::Init()
{
	SessionInterface = MakeShareable(new FOnlineSessionMLTK(this));
	return true;
}

FString FOnlineSubsystemMLTK::GetAppId() const
{
	return "";
}

FText FOnlineSubsystemMLTK::GetOnlineServiceName() const
{
	return FText::FromString("");
}
