#include <stdio.h>

#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"

#include "dhs_configuration.h"
#include "dhs_wifi.h"
#include "dhs_mqtt_connection.h"
#include "dhs_atecc.h"

#include "esp_log.h"

void app_main(void)
{
  char* config = get_configuration();
  printf("%s\n", config);
  free(config);

  // initialize ESP-DHS (device hardening system)
  ESP_ERROR_CHECK(nvs_flash_init());
  wifi_init_station();  // esp_netif_init() and esp_event_loop_create_default() are called inside here
  mqtt_app_start();
  init_atecc();

  // Memory Optimization Tests
  /* int before = 0;
  for (int i = 0; i < 20; i++)
  {
    //atca_ecdsa_test();
    char* json_res = get_configuration();
    free(json_res);
    int new = esp_get_free_heap_size();
    if(before == 0) {
      before = new;
    }
    printf("USED MEMORY: %d (before: %d, after: %d)\n", before - new, before, new);
    before = new;
  } */
  

  // initialize UA (user application)
  
}

