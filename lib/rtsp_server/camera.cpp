#include <camera.h>

#include <memory.h>

void camera::run()
{
    if (fb)
        // return the frame buffer back to the driver for reuse
        esp_camera_fb_return(fb);

    fb = esp_camera_fb_get();
}

void camera::runIfNeeded()
{
    if (!fb)
        run();
}

int camera::getWidth()
{
    runIfNeeded();
    return fb->width;
}

int camera::getHeight()
{
    runIfNeeded();
    return fb->height;
}

size_t camera::getSize()
{
    runIfNeeded();
    return fb->len;
}

uint8_t *camera::getfb()
{
    runIfNeeded();
    return fb->buf;
}

framesize_t camera::getFrameSize()
{
    return _cam_config.frame_size;
}

void camera::setFrameSize(framesize_t size)
{
    _cam_config.frame_size = size;
}

pixformat_t camera::getPixelFormat()
{
    return _cam_config.pixel_format;
}

void camera::setPixelFormat(pixformat_t format)
{
    switch (format)
    {
    case PIXFORMAT_RGB565:
    case PIXFORMAT_YUV422:
    case PIXFORMAT_GRAYSCALE:
    case PIXFORMAT_JPEG:
        _cam_config.pixel_format = format;
        break;
    default:
        _cam_config.pixel_format = PIXFORMAT_GRAYSCALE;
        break;
    }
}

esp_err_t camera::init(camera_config_t config)
{
    memset(&_cam_config, 0, sizeof(_cam_config));
    memcpy(&_cam_config, &config, sizeof(config));

    esp_err_t err = esp_camera_init(&_cam_config);
    if (err != ESP_OK)
    {
        printf("Camera probe failed with error 0x%x", err);
        return err;
    }
    // ESP_ERROR_CHECK(gpio_install_isr_service(0));

    return ESP_OK;
}
