#ifdef CONFIG_ATECC_CONNECTED
  #define ATECC_CONNECTED true
#else
  #define ATECC_CONNECTED false
#endif

void dhs_atecc_init();
bool dhs_atecc_get_status();
bool dhs_atecc_get_random_number(uint8_t[32]);