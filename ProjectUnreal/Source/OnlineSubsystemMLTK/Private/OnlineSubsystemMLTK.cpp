#include "OnlineSubsystemMLTK.h"

IOnlineSessionPtr FOnlineSubsystemMLTK::GetSessionInterface() const
{
	return nullptr;
}

IOnlineFriendsPtr FOnlineSubsystemMLTK::GetFriendsInterface() const
{
	return nullptr;
}

bool FOnlineSubsystemMLTK::Init()
{
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
