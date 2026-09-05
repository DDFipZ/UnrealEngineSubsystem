#pragma once
#include <future>
#include <unordered_map>
#include "rtc/peerconnection.hpp"

class OnlineSubsystemPluginLibraryWrapper : public std::enable_shared_from_this<OnlineSubsystemPluginLibraryWrapper>
{
	template <class T>
	static std::weak_ptr<T> make_weak_ptr(std::shared_ptr<T> ptr) { return ptr; }
	std::string localId;
	std::string sessionId;
	std::string webserviceUrl;
	std::unordered_map<std::string, std::shared_ptr<rtc::PeerConnection>> peerConnectionMap;
	std::unordered_map<std::string, std::shared_ptr<rtc::DataChannel>> dataChannelMap;
	std::shared_ptr<rtc::DataChannel> localDataChannel;
	std::shared_ptr<rtc::PeerConnection> createPeerConnection(std::string id);
	rtc::Configuration config;
public:
	
	OnlineSubsystemPluginLibraryWrapper();
	void init(std::string inSessionId, std::string inWebserviceUrl);
	
	
};
