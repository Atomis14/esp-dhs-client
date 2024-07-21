idf_component_register(SRCS "configuration.c"
                    INCLUDE_DIRS "include"
                    REQUIRES efuse bootloader_support spi_flash configuration json
                    )

#[[
  bootloader_support is needed for esp_flash_encrypt.h
  spi_flash is needed as a requirement for bootloader_support
]]