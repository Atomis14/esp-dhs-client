idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES
                      nvs_flash mbedtls
                      dhs_configuration dhs_wifi dhs_mqtt dhs_atecc
                      ua_main
                      esp32_perfmon
                    )