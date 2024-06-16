#include <stdio.h>
#include <esp_mac.h>
#include <esp_idf_version.h>
#include <esp_chip_info.h>
#include <esp_flash_encrypt.h>
#include <esp_efuse.h>
#include <esp_efuse_table.h>
#include "print.h"
#include "configuration.h"

void get_configuration()
{
  ////////////////////////// MAC Address

  printf("\n----------------------- MAC Addresses\n");

  uint8_t base_mac_address[6];
  uint8_t efuse_mac_addr_default[6];
  uint8_t efuse_mac_addr_custom[6];

  esp_base_mac_addr_get(base_mac_address);           // address which was set by esp_base_mac_addr_set
  esp_efuse_mac_get_default(efuse_mac_addr_default); // factory-programmed address
  esp_efuse_mac_get_custom(efuse_mac_addr_custom);   // previously to BLK3 written base address

  printf("Base MAC Address:\t\t");
  print_uint8_t(base_mac_address, 6, ':');

  printf("EFUSE Default MAC:\t\t");
  print_uint8_t(efuse_mac_addr_default, 6, ':');

  printf("EFUSE Custom MAC:\t\t");
  print_uint8_t(efuse_mac_addr_custom, 6, ':');

  ////////////////////////// ESP IDF Version

  printf("\n----------------------- ESP IDF Version\n");

  const char *idf_version = esp_get_idf_version();

  printf("ESP IDF Version:\t\t");
  print_char(idf_version, '\0');

  ////////////////////////// Chip Info

  printf("\n----------------------- Chip Info\n");

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  printf("Chip Cores:\t\t\t%d\n", chip_info.cores);
  printf("Chip Features:\t\t\t%lu\n", chip_info.features);
  printf("Chip Model:\t\t\t%d\n", chip_info.model);
  printf("Chip Revision:\t\t\t%hi\n", chip_info.revision);

  ////////////////////////// Flash Encryption

  printf("\n----------------------- Flash Encryption\n");

  bool flash_encryption_enabled = esp_flash_encryption_enabled();
  printf("Flash Encryption Enabled:\t%d\n", flash_encryption_enabled);

  esp_flash_enc_mode_t flash_encryption_mode = esp_get_flash_encryption_mode();
  printf("Flash Encryption Mode:\t\t%d\n", flash_encryption_mode);

  ////////////////////////// Secure Boot

  printf("\n----------------------- Secure Boot\n");

  // https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/security/secure-boot-v2.html#secure-boot-v2
  bool secure_boot_enabled = esp_efuse_read_field_bit(ESP_EFUSE_SECURE_BOOT_EN);
  printf("Secure Boot Enabled:\t\t%d\n", secure_boot_enabled);

  // https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/security/secure-boot-v2.html#key-revocation
  // 0: (conservative) key is only revoked after migration to a new key
  // 1: (aggressive) the key is revoked as soon as verification with this key fails
  bool secure_boot_aggressive_revoke_enabled = esp_efuse_read_field_bit(ESP_EFUSE_SECURE_BOOT_AGGRESSIVE_REVOKE);
  printf("Aggressive Key Revoke Enabled:\t%d\n", secure_boot_aggressive_revoke_enabled);

  // https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/security/security.html#uart-download-mode
  // 0: can flash new firmware to the device
  // 1: cannot flash a new firmware to the device
  bool download_mode_disabled = esp_efuse_read_field_bit(ESP_EFUSE_DIS_DOWNLOAD_MODE);
  printf("Download Mode Disabled:\t\t%d\n", download_mode_disabled);

  ////////////////////////// Miscellaneous

  printf("\n----------------------- Miscellaneous\n");

  // https://docs.espressif.com/projects/esp-idf/en/v5.2.2/esp32s3/security/security.html#uart-download-mode
  // 1: prevents any arbitrary code from being executed through UART download and limits available commands to update SPI config
  bool security_download_enabled = esp_efuse_read_field_bit(ESP_EFUSE_ENABLE_SECURITY_DOWNLOAD);
  printf("Security Download Enabled:\t%d\n", security_download_enabled);

  // https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/system/ota.html#anti-rollback
  // OTA Anti Rollback: in the bootloader, the security version of the selected image must be >= than this value
  // --> rollback to applications with lower security version is prevented
  uint8_t buf[2] = { 0 };
  esp_efuse_read_field_blob(ESP_EFUSE_SECURE_VERSION, &buf, esp_efuse_get_field_size(ESP_EFUSE_SECURE_VERSION));
  printf("OTA Secure Version Number:\t");
  print_uint8_t(buf, 2, '\0');
  printf("\n");

  ////////////////////////// Signed App Images



  ////////////////////////// GPIO Pins



  //////////////////////////
  // other things to read out for the certificate
  // partition table, content of the efuses, hash of application
}
