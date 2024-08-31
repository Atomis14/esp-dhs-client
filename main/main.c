#include <stdio.h>

#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"

#include "dhs_configuration.h"
#include "dhs_wifi.h"
#include "dhs_mqtt.h"
#include "dhs_atecc.h"

#include "ua_main.h"

// #include "esp_log.h"

#include "esp32_perfmon.h"

void app_main(void)
{
  if(ATECC_CONNECTED) {
    dhs_atecc_init();
  }

  char* config = dhs_config_get();
  printf("%s\n", config);
  free(config);

  // initialize ESP-DHS (device hardening system)
  ESP_ERROR_CHECK(nvs_flash_init());
  dhs_wifi_init();  // esp_netif_init() and esp_event_loop_create_default() are called inside here
  dhs_mqtt_init();

  //perfmon_start();

  // initialize and start user application
  //ua_main_init(); 

  // Memory Optimization Tests
  /* int before = 0;
  for (int i = 0; i < 20; i++)
  {
    //atca_ecdsa_test();
    char* json_res = dhs_config_get();
    free(json_res);
    int new = esp_get_free_heap_size();
    if(before == 0) {
      before = new;
    }
    printf("USED MEMORY: %d (before: %d, after: %d)\n", before - new, before, new);
    before = new;
  } */
}

