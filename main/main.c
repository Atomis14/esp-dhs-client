#include <stdio.h>
#include <esp_mac.h>
#include <esp_idf_version.h>
#include <esp_chip_info.h>

void print_char(char *string) {
  for(char *i = string; *i != '\0'; i++) {
    printf("%c", *i);
  }
  printf("\n");
}

void print_uint8_t(uint8_t *string, int length) {
  for (int i = 0; i < length; i++)
  {
    printf("%x ", string[i]);
  }
  printf("\n");
}

void get_security_configurations()
{
  ////////////////////////// MAC Address

  uint8_t base_mac_address[6];
  uint8_t efuse_mac_addr_default[6];
  uint8_t efuse_mac_addr_custom[6];

  esp_base_mac_addr_get(base_mac_address);  // address which was set by esp_base_mac_addr_set
  esp_efuse_mac_get_default(efuse_mac_addr_default);  // factory-programmed address
  esp_efuse_mac_get_custom(efuse_mac_addr_custom);  // previously to BLK3 written base address

  print_uint8_t(base_mac_address, 6);
  print_uint8_t(efuse_mac_addr_default, 6);
  print_uint8_t(efuse_mac_addr_custom, 6);

  ////////////////////////// ESP IDF Version

  const char *idf_version = esp_get_idf_version();

  print_char(idf_version);

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
