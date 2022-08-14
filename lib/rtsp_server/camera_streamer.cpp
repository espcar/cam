
#include "camera_streamer.h"
#include <assert.h>


camera_streamer::camera_streamer(SOCKET aClient, camera &cam) : CStreamer(aClient, cam.getWidth(), cam.getHeight()), m_cam(cam)
{
    printf("Created streamer width=%d, height=%d\n", cam.getWidth(), cam.getHeight());
}

void camera_streamer::streamImage(uint32_t curMsec)
{
    m_cam.run();// queue up a read for next time

    BufPtr bytes = m_cam.getfb();
    streamFrame(bytes, m_cam.getSize(), curMsec);
}
