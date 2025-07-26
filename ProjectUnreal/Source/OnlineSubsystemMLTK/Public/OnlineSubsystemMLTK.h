#pragma once
#include "OnlineSubsystemMLTKModule.h"
#include "OnlineSubsystemImpl.h"
class FOnlineSessionMLTK;
typedef TSharedPtr<class FOnlineSessionMLTK, ESPMode::ThreadSafe> FOnlineSessionMLTKPtr;

class ONLINESUBSYSTEMMLTK_API FOnlineSubsystemMLTK : public FOnlineSubsystemImpl
{
public:
	/** Interface to the session services */
	FOnlineSessionMLTKPtr SessionInterface;
	virtual IOnlineSessionPtr GetSessionInterface() const override;
	virtual IOnlineFriendsPtr GetFriendsInterface() const override;
	virtual bool Init() override;
	virtual FString GetAppId() const override;
	virtual FText GetOnlineServiceName() const override;

	explicit FOnlineSubsystemMLTK(const FName& InInstanceName)
		: FOnlineSubsystemImpl(MLTK_ONLINESUBSYSTEM , InInstanceName)
	{
	}
};
typedef TSharedPtr<FOnlineSubsystemMLTK, ESPMode::ThreadSafe> FOnlineSubsystemMLTKPtr;