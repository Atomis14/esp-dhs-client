#include <stdio.h>

#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"

#include "print.h"
#include "configuration.h"
#include "serial.h"
#include "wifi.h"
#include "mqtt_connection.h"

void app_main(void)
{
  get_configuration();

  ESP_ERROR_CHECK(nvs_flash_init());
  wifi_init_station();  // esp_netif_init() and esp_event_loop_create_default() are called inside here
  mqtt_app_start();
}

