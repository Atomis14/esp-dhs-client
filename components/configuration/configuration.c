#include <stdio.h>
#include <esp_mac.h>
#include <esp_idf_version.h>
#include <esp_chip_info.h>
#include <esp_flash_encrypt.h>
#include <esp_secure_boot.h>
#include <esp_efuse.h>
#include <esp_efuse_table.h>
#include <cJSON.h>

#include "configuration.h"

/////// menuconfig options

#ifdef CONFIG_ESP_SYSTEM_MEMPROT_FEATURE
  #define MEMORY_PROTECTION_ENABLED 1
#else
  #define MEMORY_PROTECTION_ENABLED 0
#endif

#ifdef CONFIG_ESP_SYSTEM_MEMPROT_FEATURE_LOCK
  #define MEMORY_PROTECTION_LOCKED 1
#else
  #define MEMORY_PROTECTION_LOCKED 0
#endif

/////// end menuconfig options

void format_mac_address(uint8_t *address, char* buffer) {
  snprintf(buffer, 18, "%X:%X:%X:%X:%X:%X",
    address[0], address[1], address[2],
    address[3], address[4], address[5]);
}

char* get_configuration()
{
  cJSON *configuration = cJSON_CreateObject();

  ////////////////////////// MAC Addresses

  char buffer[18];  // buffer for temporarily storing the MAC addresses for formatting

  // address which was set by esp_base_mac_addr_set
  uint8_t base_mac_address[6];
  esp_base_mac_addr_get(base_mac_address);
  format_mac_address(base_mac_address, buffer);
  cJSON_AddStringToObject(configuration, "base_mac_address", buffer);

  // factory-programmed address
  uint8_t efuse_mac_addr_default[6];
  esp_efuse_mac_get_default(efuse_mac_addr_default);
  format_mac_address(efuse_mac_addr_default, buffer);
  cJSON_AddStringToObject(configuration, "efuse_default_mac", buffer);

  // previously to BLK3 written base address
  uint8_t efuse_mac_addr_custom[6];
  esp_efuse_mac_get_custom(efuse_mac_addr_custom);
  format_mac_address(efuse_mac_addr_custom, buffer);
  cJSON_AddStringToObject(configuration, "efuse_custom_mac", buffer);

  ////////////////////////// ESP IDF Version

  const char *idf_version = esp_get_idf_version();
  cJSON_AddStringToObject(configuration, "esp_idf_version", idf_version);

  ////////////////////////// Chip Info

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);

  cJSON_AddNumberToObject(configuration, "chip_cores", chip_info.cores);
  cJSON_AddNumberToObject(configuration, "chip_features", chip_info.features);
  cJSON_AddNumberToObject(configuration, "chip_model", chip_info.model);
  cJSON_AddNumberToObject(configuration, "chip_revision", chip_info.revision);

  ////////////////////////// Flash Encryption

  bool flash_encryption_enabled = esp_flash_encryption_enabled();
  cJSON_AddBoolToObject(configuration, "flash_encryption_enabled", flash_encryption_enabled);

  esp_flash_enc_mode_t flash_encryption_mode = esp_get_flash_encryption_mode();
  cJSON_AddNumberToObject(configuration, "flash_encryption_mode", flash_encryption_mode);

  ////////////////////////// Secure Boot

  // https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/security/secure-boot-v2.html#secure-boot-v2
  bool secure_boot_enabled = esp_secure_boot_enabled();
  cJSON_AddBoolToObject(configuration, "secure_boot_enabled", secure_boot_enabled);

  // https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/security/secure-boot-v2.html#key-revocation
  // 0: (conservative) key is only revoked after migration to a new key
  // 1: (aggressive) the key is revoked as soon as verification with this key fails
  bool secure_boot_aggressive_revoke_enabled = esp_efuse_read_field_bit(ESP_EFUSE_SECURE_BOOT_AGGRESSIVE_REVOKE);
  cJSON_AddBoolToObject(configuration, "aggressive_key_revoke_enabled", secure_boot_aggressive_revoke_enabled);

  // https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/security/security.html#uart-download-mode
  // 0: can flash new firmware to the device
  // 1: cannot flash a new firmware to the device
  bool download_mode_disabled = esp_efuse_read_field_bit(ESP_EFUSE_DIS_DOWNLOAD_MODE);
  cJSON_AddBoolToObject(configuration, "download_mode_disabled", download_mode_disabled);

  ////////////////////////// Signed App Images

  ////////////////////////// Memory Protection
  // https://docs.espressif.com/projects/esp-idf/en/v5.2.2/esp32s3/security/security.html#memory-protection

  // https://docs.espressif.com/projects/esp-idf/en/v5.2.2/esp32s3/api-reference/kconfig.html#config-esp-system-memprot-feature
  // if enabled, memory access is monitored for permission violations
  bool memory_protection_enabled = MEMORY_PROTECTION_ENABLED;
  cJSON_AddBoolToObject(configuration, "memory_protection_enabled", memory_protection_enabled);

  // https://docs.espressif.com/projects/esp-idf/en/v5.2.2/esp32s3/api-reference/kconfig.html#config-esp-system-memprot-feature-lock
  // if enabled, memory protection cannot be reset until next boot
  bool memory_protection_locked = MEMORY_PROTECTION_LOCKED;
  cJSON_AddBoolToObject(configuration, "memory_protection_locked", memory_protection_locked);

  ////////////////////////// Miscellaneous

  // https://docs.espressif.com/projects/esp-idf/en/v5.2.2/esp32s3/security/security.html#uart-download-mode
  // 1: prevents any arbitrary code from being executed through UART download and limits available commands to update SPI config
  bool security_download_enabled = esp_efuse_read_field_bit(ESP_EFUSE_ENABLE_SECURITY_DOWNLOAD);
  cJSON_AddBoolToObject(configuration, "security_download_enabled", security_download_enabled);

  // https://docs.espressif.com/projects/esp-idf/en/stable/esp32s3/api-reference/system/ota.html#anti-rollback
  // OTA Anti Rollback: in the bootloader, the security version of the selected image must be >= than this value
  // --> rollback to applications with lower security version is prevented
  uint16_t secure_version;
  esp_efuse_read_field_blob(ESP_EFUSE_SECURE_VERSION, &secure_version, esp_efuse_get_field_size(ESP_EFUSE_SECURE_VERSION));
  cJSON_AddNumberToObject(configuration, "anti_rollback_secure_version", secure_version);


  ////////////////////////// GPIO Pins



  //////////////////////////
  // other things to read out for the certificate
  // partition table, content of the efuses, hash of application


  return cJSON_Print(configuration);
  //printf("\nJSON:\n%s\n", json_res);
}