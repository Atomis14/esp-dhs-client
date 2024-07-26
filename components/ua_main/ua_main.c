#include <stdio.h>
#include "esp_log.h"
#include "ua_blink.h"
#include "ua_main.h"


static const char *TAG = "ua_main";


void start_user_application()
{
  ESP_LOGI(TAG, "Started user application");

  int temperature = -5;

  configure_led();
  blink_led(temperature);
}
