#include "OnlineSubsystemPluginLibraryWrapper.h"

#include <future>
#include <cstdlib>
#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"
#include "rtc/global.hpp"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

OnlineSubsystemPluginLibraryWrapper::OnlineSubsystemPluginLibraryWrapper()
{
}

std::shared_ptr<rtc::PeerConnection> OnlineSubsystemPluginLibraryWrapper::createPeerConnection(std::string id)
{
	auto pc = std::make_shared<rtc::PeerConnection>(config);

	pc->onStateChange(
		[](rtc::PeerConnection::State state) { std::cout << "State: " << state << std::endl; });

	pc->onGatheringStateChange([](rtc::PeerConnection::GatheringState state) {
		std::cout << "Gathering State: " << state << std::endl;
	});

	pc->onLocalDescription([weakSelf = weak_from_this()](const rtc::Description& Description) {
		std::string typeStr = std::string(Description.typeString());
		std::string descStr = Description.generateSdp();
		
		AsyncTask(ENamedThreads::GameThread, [typeStr, descStr, weakSelf]()
		{
			auto self = weakSelf.lock();
			if (!self)
				return;

			// POST SDP to webservice
			TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
			FString Url = FString(self->webserviceUrl.c_str()) + TEXT("/session/") + FString(self->sessionId.c_str()) + TEXT("/offer");
			Request->SetURL(*Url);
			Request->SetVerb(TEXT("POST"));
			Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

			nlohmann::json message = {{"type", typeStr}, {"description", descStr}};
			FString Payload = FString(message.dump().c_str());
			Request->SetContentAsString(Payload);

			Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
			{
				if (bWasSuccessful && Response.IsValid())
				{
					UE_LOG(LogTemp, Warning, TEXT("✅ SDP Posted to webservice: %s"), *Response->GetContentAsString());
				}
				else
				{
					UE_LOG(LogTemp, Error, TEXT("❌ Failed to post SDP to webservice"));
				}
			});

			Request->ProcessRequest();
			std::cout << "Local Description Posted: " << message.dump() << std::endl;
		});	
	});

	pc->onLocalCandidate([weakSelf = weak_from_this()](const rtc::Candidate& candidate) {
		std::string candStr = candidate.candidate();
		
		AsyncTask(ENamedThreads::GameThread, [candStr, weakSelf]()
		{
			auto self = weakSelf.lock();
			if (!self)
				return;

			// POST ICE candidate to webservice
			TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
			FString Url = FString(self->webserviceUrl.c_str()) + TEXT("/session/") + FString(self->sessionId.c_str()) + TEXT("/candidate");
			Request->SetURL(*Url);
			Request->SetVerb(TEXT("POST"));
			Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

			nlohmann::json message = {{"candidate", candStr}};
			FString Payload = FString(message.dump().c_str());
			Request->SetContentAsString(Payload);

			Request->OnProcessRequestComplete().BindLambda([](FHttpRequestPtr Req, FHttpResponsePtr Response, bool bWasSuccessful)
			{
				if (bWasSuccessful && Response.IsValid())
				{
					UE_LOG(LogTemp, Display, TEXT("✅ Candidate posted to webservice"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("⚠️ Failed to post candidate to webservice"));
				}
			});

			Request->ProcessRequest();
		});
	});

	pc->onDataChannel([id, weakSelf = weak_from_this()](const std::shared_ptr<rtc::DataChannel>& dc) {
		std::cout << "DataChannel from " << id << " received with label \"" << dc->label() << "\""
				  << std::endl;
		
		dc->onOpen([id, wdc = make_weak_ptr(dc), weakSelf]() {
        AsyncTask(ENamedThreads::GameThread, [id, wdc, weakSelf]() {
            auto self = weakSelf.lock();
            auto dc = wdc.lock();
            if (!self || !dc)
                return;
            dc->send("Hello from " + self->localId);
        });
    });

    dc->onClosed([id]() {
        AsyncTask(ENamedThreads::GameThread, [id]() {
            UE_LOG(LogTemp, Display, TEXT("DataChannel from %s closed"), *FString(id.c_str()));
        });
    });

    dc->onMessage([id](auto data) {
        AsyncTask(ENamedThreads::GameThread, [id, data]() {
            if (std::holds_alternative<std::string>(data))
            {
            	UE_LOG(LogTemp, Log, TEXT("Message from %s: %s"), *FString(id.c_str()), *FString(std::get<std::string>(data).c_str()));
            }
            else
            {
            	UE_LOG(LogTemp, Log, TEXT("Binary message from %s, size=%d"), *FString(id.c_str()), (int32)std::get<rtc::binary>(data).size());
            }
        });
    });

	AsyncTask(ENamedThreads::GameThread, [id, dc, weakSelf]() {
		auto self = weakSelf.lock();
		if (!self)
			return;
		self->dataChannelMap.emplace(id, dc);
});
	});

	AsyncTask(ENamedThreads::GameThread, [id, pc, weakSelf = weak_from_this()]() {
		auto self = weakSelf.lock();
		if (!self)
			return;
		self->peerConnectionMap.emplace(id, pc);
	});

	return pc;
}

void OnlineSubsystemPluginLibraryWrapper::init(std::string inSessionId, std::string inWebserviceUrl)
{
	std::string stunServer = "stun:stun.l.google.com:19302";
	config.iceServers.emplace_back(stunServer);

	std::cout << "ICE UDP mux enabled" << std::endl;
	config.enableIceUdpMux = true;

	sessionId = inSessionId;
	webserviceUrl = inWebserviceUrl;
	
	localId = std::to_string(rand() % 10000);
	std::cout << "The local ID is " << localId << std::endl;
	std::cout << "Session ID is " << sessionId << std::endl;
	
	auto pc = createPeerConnection(localId);
	pc->createOffer();
}

