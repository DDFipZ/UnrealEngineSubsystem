// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceMLTK.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

const static FName SESSION_NAME = TEXT("My Session Game");

void UGameInstanceMLTK::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Initialized Game instance!"));
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Subsystem in use: %s"), *Subsystem->GetSubsystemName().ToString());
		UE_LOG(LogTemp, Warning, TEXT("Instancename: %s"), *Subsystem->GetInstanceName().ToString());
		SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UGameInstanceMLTK::OnCreateSessionComplete);
		}
		IOnlineSessionPtr MyOnlineSession = Subsystem->GetSessionInterface();
		FOnlineSessionSearch* SessionSearch = new FOnlineSessionSearch();
	}
	
}

void UGameInstanceMLTK::Host()
{
	if(SessionInterface.IsValid())
	{
		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if(ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		} 
		CreateSession();
	}
}

void UGameInstanceMLTK::CreateSession()
{
	if(SessionInterface.IsValid())
	{
		FOnlineSessionSettings SessionSettings;
		// SessionSettings.bIsLANMatch = false;
		SessionSettings.NumPublicConnections = 20;
		SessionSettings.bShouldAdvertise = true;
		SessionSettings.bUsesPresence = true;
		SessionSettings.bAllowJoinInProgress = true;
		SessionSettings.bUseLobbiesIfAvailable = true;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);		
	}
}

void UGameInstanceMLTK::OnCreateSessionComplete(FName SessionName, bool bSucceeded)
{
	if(!bSucceeded) return;
	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if(!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/FirstPerson/Maps/FirstPersonMap??listen");
}

void UGameInstanceMLTK::ConnectSession()
{
	FURL ConnectionURL;
	ConnectionURL.Host = TEXT("localhost:7777");
	GetWorld()->GetFirstPlayerController()->ClientTravel(ConnectionURL.ToString(), ETravelType::TRAVEL_Absolute);
}
