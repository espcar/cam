#pragma once

#include <list>
#include <WiFiServer.h>
#include <ESPmDNS.h>
#include <camera.h>
#include <CRtspSession.h>
#include <arduino-timer.h>

class rtsp_server : public WiFiServer
{
public:
	rtsp_server(camera &cam, unsigned long interval, int port = 554);

	void doLoop();

private:
	struct rtsp_client
	{
	public:
		rtsp_client(const WiFiClient &client, camera &cam);

		WiFiClient wifi_client;
		// Streamer for UDP/TCP based RTP transport
		std::shared_ptr<CStreamer> streamer;
		// RTSP session and state
		std::shared_ptr<CRtspSession> session;
	};

	camera cam_;
	std::list<std::unique_ptr<rtsp_client>> clients_;
	uintptr_t task_;
	Timer<> timer_;

	static bool client_handler(void *);
};