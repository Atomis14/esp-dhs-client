#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ua_blink.h"
#include "ua_main.h"
#include "dhs_atecc.h"

#ifdef CONFIG_UA_LED_ACTIVE
  #define LED_ACTIVATED true
#else
  #define LED_ACTIVATED false
#endif

#ifdef CONFIG_UA_LOGS_ACTIVE
  #define LOGS_ACTIVATED true
#else
  #define LOGS_ACTIVATED false
#endif

static const char *TAG = "ua_main";


void ua_main_init()
{
  ESP_LOGI(TAG, "Started user application");

  if(!ATECC_CONNECTED) {
    ESP_LOGI(TAG, "User application cannot run without connected ATECC608.");
    return;
  }

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
        if(LOGS_ACTIVATED) {
          ESP_LOGI(TAG, "Current color (r,g,b): %d,%d,%d", red, green, blue);
        }
        if(LED_ACTIVATED) {
          ua_set_led_color(red, green, blue);
        }
        vTaskDelay(CONFIG_UA_DURATION / portTICK_PERIOD_MS);
      }
    }
  }
}
