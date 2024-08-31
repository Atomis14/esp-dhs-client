# ESP-DHS Client

**ESP**32-S3 **D**evice **H**ardening **S**ystem Client

Firmware running on the ESP32-S3 that extracts the security configuration upon request and sends it to the server.

## Setup

Project built using VS Code and ESP-IDF extensions v1.7.1 (did not work with newer versions of the extension)

For the ESP-DHS to work, it is necessary that the firmware was built manually at least once (i.e. the `/build` directory should not be empty).

The following configurations need to be set manually before first building the project (not by writing them manually to a `sdkconfig` file, but by entering the values in the menuconfg UI):

```bash
# the custom table contains a virtual eFuse partition
CONFIG_PARTITION_TABLE_CUSTOM=y

# bigger offset needed for secure boot bootloader
CONFIG_PARTITION_TABLE_OFFSET=0x10000

# SSID of the Wi-Fi network
ESP_WIFI_SSID=<SSID>

# password of the Wi-Fi network
ESP_WIFI_PASSWORD=<PASSWORD>

# URI of the MQTT broker in the following format:
# mqtts://<username>:<password>@<fqdn>:8883
BROKER_URI=<URI>

# y if you intend to use a secure element, n otherwise
ATECC_CONNECTED=y/n

# if ATECC608B will be connected, add these additionally:
CONFIG_ATCA_MBEDTLS_ECDSA=y
CONFIG_ATCA_MBEDTLS_ECDSA_SIGN=y
CONFIG_ATCA_MBEDTLS_ECDSA_VERIFY=y
CONFIG_ATCA_I2C_SDA_PIN=14  # or any other used pin
CONFIG_ATCA_I2C_SCL_PIN=13  # or any other used pin
```
