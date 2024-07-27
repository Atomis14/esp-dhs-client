#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "ua_blink.h"

#define BLINK_GPIO 48

static const char *TAG = "ua_blink";


static led_strip_handle_t led_strip;

void ua_set_led_color(uint8_t red, uint8_t green, uint8_t blue)
{
  // set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color
  led_strip_set_pixel(led_strip, 0, red, green, blue);
  // refresh the strip to send data
  led_strip_refresh(led_strip);
}

void ua_blink_init()
{
  ESP_LOGI(TAG, "Example configured to blink addressable LED!");

  // LED strip initialization with the GPIO and pixels number
  led_strip_config_t strip_config = {
    .strip_gpio_num = BLINK_GPIO,
    .max_leds = 1, // at least one LED on board
  };

  led_strip_rmt_config_t rmt_config = {
    .resolution_hz = 10 * 1000 * 1000, // 10MHz
    .flags.with_dma = false,
  };
  ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));

  led_strip_clear(led_strip);
}