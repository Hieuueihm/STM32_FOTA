#include "uart.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>

// void usart2_isr(void)
// {
// }
void uart_setup(void)
{
    rcc_periph_clock_enable(RCC_AFIO);

    rcc_periph_clock_enable(RCC_USART1);
    usart_disable(USART1);
    usart_set_mode(USART1, USART_MODE_TX_RX);

    usart_set_baudrate(USART1, 115200);
    usart_set_databits(USART1, 8);
    usart_set_stopbits(USART1, USART_STOPBITS_1);
    usart_set_parity(USART1, USART_PARITY_NONE);
    usart_set_flow_control(USART1, USART_FLOWCONTROL_NONE);

    usart_enable(USART1);
}
void uart_write(uint8_t *data, const uint32_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        uart_write_byte(data[i]);
    }
}
void uart_write_byte(uint8_t data)
{
    usart_send_blocking(USART1, (uint16_t)data);
}
// uint32_t uart_read(uint8_t *data, const uint32_t length)
// {
// }
// uint8_t uart_read_byte(void)
// {
//     uint8_t byte = 0;
//     (void)uart_read(&byte, 1);
//     return byte;
// }
// bool uart_data_available(void)
// {
// }