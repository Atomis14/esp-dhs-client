#include <stdio.h>

#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"

#include "dhs_configuration.h"
#include "dhs_wifi.h"
#include "dhs_mqtt_connection.h"
#include "dhs_atecc.h"


void app_main(void)
{
  printf("%s\n", get_configuration());
  init_atecc();

  // initialize ESP-DHS (device hardening system)
  ESP_ERROR_CHECK(nvs_flash_init());
  wifi_init_station();  // esp_netif_init() and esp_event_loop_create_default() are called inside here
  mqtt_app_start();

  // initialize UA (user application)
  
}

