idf_component_register(SRCS "mqttcomponent.c"
                    INCLUDE_DIRS "include"
                    REQUIRES
                      esp_partition nvs_flash esp_event esp_netif esp-tls app_update mqtt
                    )