#include <stdio.h>
#include <esp_mac.h>
#include <esp_idf_version.h>
#include <esp_chip_info.h>
#include <esp_flash_encrypt.h>
#include "print.h"

void get_security_configurations()
{
  ////////////////////////// MAC Address

  uint8_t base_mac_address[6];
  uint8_t efuse_mac_addr_default[6];
  uint8_t efuse_mac_addr_custom[6];

  esp_base_mac_addr_get(base_mac_address);           // address which was set by esp_base_mac_addr_set
  esp_efuse_mac_get_default(efuse_mac_addr_default); // factory-programmed address
  esp_efuse_mac_get_custom(efuse_mac_addr_custom);   // previously to BLK3 written base address

  printf("Base MAC Address:\t");
  print_uint8_t(base_mac_address, 6, ':');

  printf("EFUSE Default MAC:\t");
  print_uint8_t(efuse_mac_addr_default, 6, ':');

  printf("EFUSE Custom MAC:\t");
  print_uint8_t(efuse_mac_addr_custom, 6, ':');

  ////////////////////////// ESP IDF Version

  const char *idf_version = esp_get_idf_version();

  printf("ESP IDF Version:\t");
  print_char(idf_version, '\0');

  ////////////////////////// Chip Info

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  printf("Chip Cores:\t\t%d\n", chip_info.cores);
  printf("Chip Features:\t\t%lu\n", chip_info.features);
  printf("Chip Model:\t\t%d\n", chip_info.model);
  printf("Chip Revision:\t\t%hi\n", chip_info.revision);

  ////////////////////////// Flash Encryption

  bool flash_encryption_enabled = esp_flash_encryption_enabled();
  printf("Flash Encryption:\t%d\n", flash_encryption_enabled);

  // other things to read out for the certificate
  // partition table, content of the efuses, hash of application
}

void analyze_secure_boot()
{

}

void app_main(void)
{
  get_security_configurations();
  printf("\n");
}
