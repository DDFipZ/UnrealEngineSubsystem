// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OnlineSessionSettings.h"
#include "UWebSocketAccessor.h"
#include "GameService.generated.h"

/**
 * 
 */
UCLASS()
class ONLINESUBSYSTEMPLUGIN_API UGameService : public UObject
{
private:
	UPROPERTY()
	UWebSocketAccessor* WebSocketAccessor;
	GENERATED_BODY()
	public:
	void HelloWorld();
	void CreateSession(FName SessionName, FName SessionIP, FOnlineSessionSettings SessionSettings);
};
