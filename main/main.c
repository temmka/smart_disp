#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"

#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"


#include "sm_config.h"
#include <lcd_ili9341.h>
#include "Adafruit_GFX.h"
#include "ws2812.h"

extern const unsigned char water [];
extern const unsigned char bulb [];
extern const unsigned short bulb_45[];
extern const unsigned short mosque[];
extern const unsigned char bulb_gs[];

void ws2812_task(void *pvParameters)
{
    uint8_t anim_max = 1;
    uint16_t step = 0;
    pixel_t pixel_color;

    while (1)
    {


        step++;
        switch (step)
        {
        case 1:
            pixel_color.red = anim_max;
            pixel_color.green = 0;
            pixel_color.blue = 0;
            break;
        case 2:
            pixel_color.red = 0;
            pixel_color.green = anim_max;
            pixel_color.blue = 0;
            break;
        case 3:
            pixel_color.red = 0;
            pixel_color.green = 0;
            pixel_color.blue = anim_max;
            break;
        case 4:
            pixel_color.red = anim_max;
            pixel_color.green = anim_max;
            pixel_color.blue = anim_max;

            break;
        case 5:
            pixel_color.red = 0;
            pixel_color.green = 0;
            pixel_color.blue = 0;
            step = 0;
            break;

        default:
            step = 0;
            break;
        }



        for (uint8_t i = 0; i < 8; i++)
        {
            ws2812_set_led_pixel(i, pixel_color);
        }

        ws2812_show();

        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}



esp_err_t event_handler(void *ctx, system_event_t *event)
{
    return ESP_OK;
}


void main_display_task(void *pvParameter)
{
    il9341_init();
    il9341_write_fill_rect(0,0,320,240,ILI9341_BLACK);

    uint16_t x = 0;
    uint16_t y = 0;

    cp437(0);
    setTextWrap(1);
    setTextSize(3);

    setTextColor(ILI9341_ORANGE);
    setCursor(60, 5);
    writeText("3.81");

    setTextColor(ILI9341_GREEN);
    setCursor(60, 30);
    writeText("6.35");


    setTextColor(ILI9341_BLUE);
    setCursor(60, 65);
    writeText("0.21");

    setTextColor(ILI9341_GREEN);
    setCursor(60, 90);
    writeText("1.05");


    setTextColor(ILI9341_RED);
    setCursor(60, 125);
    writeText("+21.3");

    setTextColor(ILI9341_CYAN);
    setCursor(60, 150);
    writeText("-17.1");




    setTextColor(ILI9341_LIGHTGREY);
    setCursor(10, 220);
    writeText("12.04.2017 22:34");

    //drawRoundRect(2,2, 72, 27,2,ILI9341_LIGHTGREY);

    drawRGBBitmap(0, 5, (uint16_t*)bulb_45, 45, 45);

   // drawRGBBitmap(0, 68, (uint16_t*)mosque, 45, 45);
    drawBitmap(0, 68, (uint8_t*) water, 45, 45, ILI9341_WHITE);

    drawBitmap(0, 131, (uint8_t*) bulb, 45, 45, ILI9341_WHITE);


    uint8_t xx = 0;
    while (true)
    {
      //  drawChar(100, 100, x, ILI9341_ORANGE, ILI9341_BLACK, 8);


        if(xx)
        {
            drawBitmap(0, 131, (uint8_t*)bulb, 45, 45, ILI9341_WHITE);
            xx=0;
        }
        else
        {
            drawBitmap(0, 131, (uint8_t*)bulb, 45, 45, ILI9341_RED);
            xx=1;
        }

        vTaskDelay(300 / portTICK_PERIOD_MS);

    }
}




void app_main(void)
{

    spi_il9341_config();
    ws2812_init(PIN_WS2812_LED, CNT_WS2812_LED, RMT_CH_WS2812_LED);

    nvs_flash_init();
//    tcpip_adapter_init();
//    ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
//    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
//    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
//    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
//    wifi_config_t sta_config = {
//        .sta = {
//            .ssid = "access_point_name",
//            .password = "password",
//            .bssid_set = false
//        }
//    };
//    ESP_ERROR_CHECK( esp_wifi_set_config(WIFI_IF_STA, &sta_config) );
//    ESP_ERROR_CHECK( esp_wifi_start() );
//    ESP_ERROR_CHECK( esp_wifi_connect() );




    xTaskCreate(main_display_task, "main_display_task", 1024, NULL, 5, NULL);
    xTaskCreate(ws2812_task, "ws2812 rainbow demo", 4096, NULL, 6, NULL);


}



