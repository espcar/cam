#pragma once

#include "CStreamer.h"
#include "camera.h"

class camera_streamer : public CStreamer
{
    bool m_showBig;
    camera &m_cam;

public:
    camera_streamer(SOCKET aClient, camera &cam);

    virtual void streamImage(uint32_t curMsec);
};
