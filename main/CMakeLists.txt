idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES
                      nvs_flash
                      print configuration serial wifi
                    )