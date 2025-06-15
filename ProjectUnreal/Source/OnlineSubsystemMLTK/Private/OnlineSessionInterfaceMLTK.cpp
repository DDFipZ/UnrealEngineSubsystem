#include "OnlineSessionInterfaceMLTK.h"

#include "OnlineSubsystemMLTK.h"

FNamedOnlineSession* FOnlineSessionMLTK::AddNamedSession(FName SessionName,
                                                         const FOnlineSessionSettings& SessionSettings)
{
	return nullptr;
}

FNamedOnlineSession* FOnlineSessionMLTK::AddNamedSession(FName SessionName, const FOnlineSession& Session)
{
	return nullptr;
}

FUniqueNetIdPtr FOnlineSessionMLTK::CreateSessionIdFromString(const FString& SessionIdStr)
{
	return nullptr;
}

FNamedOnlineSession* FOnlineSessionMLTK::GetNamedSession(FName SessionName)
{
	return nullptr;
}

void FOnlineSessionMLTK::RemoveNamedSession(FName SessionName)
{
}

bool FOnlineSessionMLTK::HasPresenceSession()
{
	return false;
}

EOnlineSessionState::Type FOnlineSessionMLTK::GetSessionState(FName SessionName) const
{
	return EOnlineSessionState::Type::NoSession;
}

bool FOnlineSessionMLTK::CreateSession(int32 HostingPlayerNum, FName SessionName,
	const FOnlineSessionSettings& NewSessionSettings)
{
	return false;
}

bool FOnlineSessionMLTK::StartSession(FName SessionName)
{
	return false;
}

bool FOnlineSessionMLTK::UpdateSession(FName SessionName, FOnlineSessionSettings& UpdatedSessionSettings,
	bool bShouldRefreshOnlineData)
{
	return false;
}

bool FOnlineSessionMLTK::EndSession(FName SessionName)
{
	return false;
}

bool FOnlineSessionMLTK::DestroySession(FName SessionName, const FOnDestroySessionCompleteDelegate& CompletionDelegate)
{
	return false;
}

bool FOnlineSessionMLTK::IsPlayerInSession(FName SessionName, const FUniqueNetId& UniqueId)
{
	return false;
}

bool FOnlineSessionMLTK::StartMatchmaking(const TArray<FUniqueNetIdRef>& LocalPlayers, FName SessionName,
	const FOnlineSessionSettings& NewSessionSettings, TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	return false;
}

bool FOnlineSessionMLTK::CancelMatchmaking(int32 SearchingPlayerNum, FName SessionName)
{
	return false;
}

bool FOnlineSessionMLTK::CancelMatchmaking(const FUniqueNetId& SearchingPlayerId, FName SessionName)
{
	return false;
}

bool FOnlineSessionMLTK::FindSessions(int32 SearchingPlayerNum, const TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	return false;
}

bool FOnlineSessionMLTK::FindSessions(const FUniqueNetId& SearchingPlayerId,
	const TSharedRef<FOnlineSessionSearch>& SearchSettings)
{
	return false;
}

bool FOnlineSessionMLTK::FindSessionById(const FUniqueNetId& SearchingUserId, const FUniqueNetId& SessionId,
	const FUniqueNetId& FriendId, const FOnSingleSessionResultCompleteDelegate& CompletionDelegate)
{
	return false;
}

bool FOnlineSessionMLTK::CancelFindSessions()
{
	return false;
}

bool FOnlineSessionMLTK::PingSearchResults(const FOnlineSessionSearchResult& SearchResult)
{
	return false;
}

bool FOnlineSessionMLTK::JoinSession(int32 LocalUserNum, FName SessionName,
	const FOnlineSessionSearchResult& DesiredSession)
{
	return false;
}

bool FOnlineSessionMLTK::JoinSession(const FUniqueNetId& LocalUserId, FName SessionName,
	const FOnlineSessionSearchResult& DesiredSession)
{
	return false;
}

bool FOnlineSessionMLTK::FindFriendSession(int32 LocalUserNum, const FUniqueNetId& Friend)
{
	return false;
}

bool FOnlineSessionMLTK::FindFriendSession(const FUniqueNetId& LocalUserId, const FUniqueNetId& Friend)
{
	return false;
}

bool FOnlineSessionMLTK::FindFriendSession(const FUniqueNetId& LocalUserId, const TArray<FUniqueNetIdRef>& FriendList)
{
	return false;
}

bool FOnlineSessionMLTK::SendSessionInviteToFriend(int32 LocalUserNum, FName SessionName, const FUniqueNetId& Friend)
{
	return false;
}

bool FOnlineSessionMLTK::SendSessionInviteToFriend(const FUniqueNetId& LocalUserId, FName SessionName,
	const FUniqueNetId& Friend)
{
	return false;
}

bool FOnlineSessionMLTK::SendSessionInviteToFriends(int32 LocalUserNum, FName SessionName,
	const TArray<FUniqueNetIdRef>& Friends)
{
	return false;
}

bool FOnlineSessionMLTK::SendSessionInviteToFriends(const FUniqueNetId& LocalUserId, FName SessionName,
	const TArray<FUniqueNetIdRef>& Friends)
{
	return false;
}

bool FOnlineSessionMLTK::GetResolvedConnectString(FName SessionName, FString& ConnectInfo, FName PortType)
{
	return false;
}

bool FOnlineSessionMLTK::GetResolvedConnectString(const FOnlineSessionSearchResult& SearchResult, FName PortType,
	FString& ConnectInfo)
{
	return false;
}

FOnlineSessionSettings* FOnlineSessionMLTK::GetSessionSettings(FName SessionName)
{
	return nullptr;
}

bool FOnlineSessionMLTK::RegisterPlayer(FName SessionName, const FUniqueNetId& PlayerId, bool bWasInvited)
{
	return false;
}

bool FOnlineSessionMLTK::RegisterPlayers(FName SessionName, const TArray<FUniqueNetIdRef>& Players, bool bWasInvited)
{
	return false;
}

bool FOnlineSessionMLTK::UnregisterPlayer(FName SessionName, const FUniqueNetId& PlayerId)
{
	return false;
}

bool FOnlineSessionMLTK::UnregisterPlayers(FName SessionName, const TArray<FUniqueNetIdRef>& Players)
{
	return false;
}

void FOnlineSessionMLTK::RegisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName,
	const FOnRegisterLocalPlayerCompleteDelegate& Delegate)
{
}

void FOnlineSessionMLTK::UnregisterLocalPlayer(const FUniqueNetId& PlayerId, FName SessionName,
	const FOnUnregisterLocalPlayerCompleteDelegate& Delegate)
{
}

int32 FOnlineSessionMLTK::GetNumSessions()
{
	return 0;
}

void FOnlineSessionMLTK::DumpSessionState()
{
}

bool FOnlineSessionMLTK::CreateSession(const FUniqueNetId& HostingPlayerId, FName SessionName,
                                       const FOnlineSessionSettings& NewSessionSettings)
{
	return false;
}

FOnlineSessionMLTK::~FOnlineSessionMLTK()
{
}


