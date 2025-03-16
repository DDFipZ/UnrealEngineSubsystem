#pragma once
#include "OnlineSubsystemMLTKModule.h"
#include "OnlineSubsystemImpl.h"

class ONLINESUBSYSTEMMLTK_API FOnlineSubsystemMLTK : public FOnlineSubsystemImpl
{
public:
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