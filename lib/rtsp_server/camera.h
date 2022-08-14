#pragma once

#include <esp_camera.h>

class camera
{
public:
    camera()
    {
        fb = NULL;
    };
    ~camera(){};
    esp_err_t init(camera_config_t config);
    void run();
    size_t getSize();
    uint8_t *getfb();
    int getWidth();
    int getHeight();
    framesize_t getFrameSize();
    pixformat_t getPixelFormat();

    void setFrameSize(framesize_t size);
    void setPixelFormat(pixformat_t format);

private:
    void runIfNeeded(); // grab a frame if we don't already have one
    camera_config_t _cam_config;
    camera_fb_t *fb;
};