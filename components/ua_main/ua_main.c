#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"

#include "ua_main.h"

#define BLINK_GPIO 48

static const char *TAG = "UA";

static uint8_t s_led_state = 0;
static led_strip_handle_t led_strip;

static void blink_led(int temperature)
{
  //                     r  g  b
  uint8_t channels[3] = {0, 0, 0};
  if (temperature >= 25) { // red
    channels[0] = 255;
    channels[1] = 0;
    channels[2] = 0;
  } else if (temperature >= 10) { // yellow
    channels[0] = 94;
    channels[1] = 91;
    channels[2] = 16;
  } else if (temperature > 0) { // light blue
    channels[0] = 13;
    channels[1] = 67;
    channels[2] = 85;
  } else {  // dark blue
    channels[0] = 0;
    channels[1] = 0;
    channels[2] = 255;
  }

  /* If the addressable LED is enabled */
  if (s_led_state) {
    /* Set the LED pixel using RGB from 0 (0%) to 255 (100%) for each color */
    led_strip_set_pixel(led_strip, 0, channels[0], channels[1], channels[2]);
    /* Refresh the strip to send data */
    led_strip_refresh(led_strip);
  } else {
    // Set all LED off to clear all pixels
    led_strip_clear(led_strip);
  }
}

static void configure_led() {
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


void start_user_application()
{
  ESP_LOGI(TAG, "Started user application");

  int temperature = -5;

  configure_led();

  while (1) {
    ESP_LOGI(TAG, "Turning the LED %s!", s_led_state == true ? "ON" : "OFF");
    blink_led(temperature);
    temperature += 2;
    s_led_state = !s_led_state; // toggle LED state
    int blink_period = 500;
    vTaskDelay(blink_period / portTICK_PERIOD_MS);
  }
}
