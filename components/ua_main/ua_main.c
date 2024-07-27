#include <stdio.h>
#include "esp_log.h"
#include "ua_blink.h"
#include "ua_main.h"


static const char *TAG = "ua_main";


void ua_main_init()
{
  ESP_LOGI(TAG, "Started user application");

  int temperature = -5;

  ua_blink_init();
  ua_blink_led(temperature);
}
