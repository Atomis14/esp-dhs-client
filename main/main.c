#include <stdio.h>
#include <esp_mac.h>
#include <esp_idf_version.h>
#include <esp_chip_info.h>
#include "print.h"

void get_security_configurations()
{
  ////////////////////////// MAC Address

  uint8_t base_mac_address[6];
  uint8_t efuse_mac_addr_default[6];
  uint8_t efuse_mac_addr_custom[6];

  esp_base_mac_addr_get(base_mac_address);  // address which was set by esp_base_mac_addr_set
  esp_efuse_mac_get_default(efuse_mac_addr_default);  // factory-programmed address
  esp_efuse_mac_get_custom(efuse_mac_addr_custom);  // previously to BLK3 written base address

  print_uint8_t(base_mac_address, 6, ':');
  print_uint8_t(efuse_mac_addr_default, 6, ':');
  print_uint8_t(efuse_mac_addr_custom, 6, ':');

  ////////////////////////// ESP IDF Version

  const char *idf_version = esp_get_idf_version();

  print_char(idf_version, '\0');

  ////////////////////////// Chip Info

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  printf("%d\n", chip_info.cores);
  printf("%lu\n", chip_info.features);
  printf("%d\n", chip_info.model);
  printf("%hi\n", chip_info.revision);
  printf("\n");

  // other tings to read out for the certificate
  // partition table, content of the efuses, hash of application

  ////////////////////////// Secure Boot
}



void app_main(void)
{
  get_security_configurations();
}
