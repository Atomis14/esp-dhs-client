#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
#include "print.h"
#include "serial.h"

void establish_serial_connection()
{
  // UART configuration
  const uart_port_t uart_num = UART_NUM_2;
  uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
    .rx_flow_ctrl_thresh = 122,
  };
  ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

  // set physical UART pins
  ESP_ERROR_CHECK(uart_set_pin(uart_num, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

  // install drivers
  const int uart_buffer_size = (1024 * 2);
  QueueHandle_t uart_queue;
  ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));

  /*
  char* test_str = "XXXXXXXXXXXX.\n";
  uart_write_bytes(uart_num, (const char*)test_str, strlen(test_str));
  */

  uint8_t data[128];
  int length = 0;
  ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*)&length));
  length = uart_read_bytes(uart_num, data, length, 100);

  print_uint8_t(data, 128, '\0');

  printf("AAAAAA");
}

void send_message() {

}

void receive_message() {

}
