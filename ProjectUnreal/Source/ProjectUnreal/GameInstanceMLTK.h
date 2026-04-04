// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "GameInstanceMLTK.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTUNREAL_API UGameInstanceMLTK : public UGameInstance
{
	GENERATED_BODY()
private:
	IOnlineSessionPtr SessionInterface;
public:
	virtual void Init() override;
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void ConnectSession();

private:
	void CreateSession();
	void OnCreateSessionComplete(FName SessionName, bool bSucceeded);
};
