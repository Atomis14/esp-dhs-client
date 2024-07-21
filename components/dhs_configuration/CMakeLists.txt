idf_component_register(SRCS "dhs_configuration.c"
                    INCLUDE_DIRS "include"
                    REQUIRES efuse bootloader_support spi_flash json
                    )

#[[
  bootloader_support is needed for esp_flash_encrypt.h
  spi_flash is needed as a requirement for bootloader_support
]]