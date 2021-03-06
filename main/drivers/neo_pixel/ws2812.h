

#ifndef MAIN_WS2812_H_
#define MAIN_WS2812_H_
#include <stdint.h>
#include <driver/rmt.h>
#include <driver/gpio.h>

/**
 * @brief A data type representing the color of a pixel.
 */
typedef struct {
    /**
     * @brief The red component of the pixel.
     */
    uint8_t red;
    /**
     * @brief The green component of the pixel.
     */
    uint8_t green;
    /**
     * @brief The blue component of the pixel.
     */
    uint8_t blue;
} pixel_t;


/**
 * @brief Driver for WS2812/NeoPixel data.
 *
 * NeoPixels or WS2812s are LED devices that can illuminate in arbitrary colors with
 * 8 bits of data for each of the red, green and blue channels.  These devices can be
 * daisy chained together to produce a string of LEDs.  If we call each LED instance
 * a pixel, then when we want to set the value of a string of pixels, we need to supply
 * the data for all the pixels.  This class encapsulates setting the color value for
 * an individual pixel within the string and, once you have set up all the desired colors,
 * you can then set all the pixels in a show() operation.  The class hides from you
 * the underlying details needed to drive the devices.
 *
 * @code{.cpp}
 * WS2812 ws2812 = WS2812(
 *   16, // Pin
 *   8   // Pixel count
 * );
 * ws2812.setPixel(0, 128, 0, 0);
 * ws2812.show();
 * @endcode
 */

    void ws2812_init(gpio_num_t gpioNum, uint16_t pixelCount, int channel);
    void ws2812_show();
    void ws2812_set_color_order(char *order);
    void ws2812_set_led_rgb(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
    void ws2812_set_led_pixel(uint16_t index, pixel_t pixel);
    void ws2812_set_led_u32(uint16_t index, uint32_t pixel);
    void ws2812_set_led_hsb(uint16_t index, uint16_t hue, uint8_t saturation, uint8_t brightness);
    void ws2812_clear();




#endif /* MAIN_WS2812_H_ */
