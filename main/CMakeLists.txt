idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES efuse bootloader_support spi_flash print)

#[[
  bootloader_support is needed for esp_flash_encrypt.h
  spi_flash is needed as a requirement for bootloader_support
]]