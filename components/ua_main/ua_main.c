#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ua_blink.h"
#include "ua_main.h"
#include "dhs_atecc.h"


static const char *TAG = "ua_main";


void ua_main_init()
{
  ESP_LOGI(TAG, "Started user application");

  ua_blink_init();

  uint8_t random_number[32];
  int ret = dhs_atecc_get_random_number(random_number);
  if(ret == 0) {
    ESP_LOGE(TAG, "Cannot get random number.");
  } else {
    while(true) {
      for(int i=0; i<27; i+=3) {
        uint8_t red = random_number[i];
        uint8_t green = random_number[i+1];
        uint8_t blue = random_number[i+2];
        ESP_LOGI(TAG, "Current color (r,g,b): %d,%d,%d", red, green, blue);
        ua_set_led_color(red, green, blue);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    }
  }
}
