// Fill out your copyright notice in the Description page of Project Settings.


#include "GameService.h"

#include "HttpModule.h"
#include "UWebSocketAccessor.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void UGameService::HelloWorld()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("http://localhost:5117/session/ping")); // or your actual API endpoint
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			const FString Result = Response->GetContentAsString();
			UE_LOG(LogTemp, Warning, TEXT("✅ API Response: %s"), *Result);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ API call failed"));
		}
	});

	Request->ProcessRequest();
}

void UGameService::CreateSession(FName SessionName, FName SessionIP, FOnlineSessionSettings SessionSettings)
{
	// Build HTTP request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("http://127.0.0.1:5117/session/createsession"));
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	
	// Build JSON payload from SessionSettings
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("Name"), SessionName.ToString());
	JsonObject->SetBoolField(TEXT("bShouldAdvertise"), SessionSettings.bShouldAdvertise);
	JsonObject->SetBoolField(TEXT("bAllowJoinInProgress"), SessionSettings.bAllowJoinInProgress);
	JsonObject->SetBoolField(TEXT("bAllowJoinViaPresence"), SessionSettings.bAllowJoinViaPresence);
	JsonObject->SetBoolField(TEXT("bAllowJoinViaPresenceFriendsOnly"), SessionSettings.bAllowJoinViaPresenceFriendsOnly);
	JsonObject->SetBoolField(TEXT("bAllowInvites"), SessionSettings.bAllowInvites);
	JsonObject->SetNumberField(TEXT("NumPublicConnections"), SessionSettings.NumPublicConnections);
	JsonObject->SetNumberField(TEXT("BuildUniqueID"), 15);
	
	// Serialize JSON
	FString Payload;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Payload);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	Request->SetContentAsString(Payload);

	// Send request and setup peer connection on success
	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
	{
		if (bWasSuccessful && Response.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("✅ CreateSession Response: %s"), *Response->GetContentAsString());
			
			// Parse response to get session ID
			TSharedPtr<FJsonObject> JsonResponse;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
			if (FJsonSerializer::Deserialize(Reader, JsonResponse) && JsonResponse.IsValid())
			{
				if (JsonResponse->HasField(TEXT("sessionId")))
				{
					FString SessionId = JsonResponse->GetStringField(TEXT("sessionId"));
					
					// Now initialize peer connection with session ID
					if (WebSocketAccessor == nullptr)
						WebSocketAccessor = NewObject<UWebSocketAccessor>();
					
					FString WebserviceUrl = TEXT("http://127.0.0.1:5117");
					WebSocketAccessor->Init(SessionId, WebserviceUrl);
					
					UE_LOG(LogTemp, Warning, TEXT("✅ Peer connection initialized for session: %s"), *SessionId);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("❌ CreateSession failed"));
		}
	}); 

	Request->ProcessRequest();
}
