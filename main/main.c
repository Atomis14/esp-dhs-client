#include <stdio.h>
#include "nvs_flash.h"
#include "print.h"
#include "configuration.h"
#include "serial.h"
#include "wifi.h"

void app_main(void)
{
  //Initialize NVS
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  // get_configuration();
  // establish_serial_connection();
  wifi_init_sta();
}
