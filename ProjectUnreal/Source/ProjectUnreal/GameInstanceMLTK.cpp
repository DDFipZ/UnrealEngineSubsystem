// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceMLTK.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

void UGameInstanceMLTK::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialized Game instance!"));
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Subsystem in use: %s"), *Subsystem->GetSubsystemName().ToString());
		UE_LOG(LogTemp, Warning, TEXT("Instancename: %s"), *Subsystem->GetInstanceName().ToString());
		IOnlineSessionPtr MyOnlineSession = Subsystem->GetSessionInterface();
		FOnlineSessionSearch* SessionSearch = new FOnlineSessionSearch();
		MyOnlineSession->FindSessions(0,TSharedRef<FOnlineSessionSearch>(SessionSearch));
	}
	
}
