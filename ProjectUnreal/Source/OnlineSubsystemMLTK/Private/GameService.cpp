// Fill out your copyright notice in the Description page of Project Settings.


#include "GameService.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

void UGameService::HelloWorld()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(TEXT("http://localhost:5117/weatherforecast/helloworld")); // or your actual API endpoint
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
