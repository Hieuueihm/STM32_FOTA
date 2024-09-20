#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "timer.h"
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/cm3/scb.h>
#include "common_defines.h"
#define LED_PORT (GPIOC)
#define LED_PIN (GPIO13)
#define BOOTLOADER_SIZE (0x8000u)

static inline void vector_setup(void)
{
    // SCB_VTOR = BOOTLOADER_SIZE;
}

volatile uint64_t ticks = 0;
void sys_tick_handler(void)
{
    ticks++;
}
static inline uint64_t get_ticks(void)
{
    return ticks;
}
static inline void rcc_setup(void)
{
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_24MHZ]);
}
static inline void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
}
static inline void delay_cycles(uint32_t cycle)
{
    for (uint32_t i = 0; i < cycle; i++)
    {
        __asm__("nop");
    }
}
static inline void systick_setup(void)
{
    systick_set_frequency(1000, 24000000);
    systick_counter_enable();
    systick_interrupt_enable();
}
int main(void)
{
    vector_setup();
    rcc_setup();
    gpio_setup();
    systick_setup();
    //   timer_setup();
    //     float duty_cycle = 0.0f;
    //       timer_pwm_set_duty_cycle(duty_cycle);
    uint64_t start_time = get_ticks();
    while (1)
    {

        delay_cycles(1000000);
        if (get_ticks() - start_time >= 1000)
        {
            gpio_toggle(LED_PORT, LED_PIN);

            start_time = get_ticks();
        }
    }
    return 0;
}