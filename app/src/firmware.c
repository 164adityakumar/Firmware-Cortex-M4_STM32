#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/scb.h>

#include "core/system.h"
#include "core/timer.h"

#define BOOTLOADER_SIZE (0x8000U)

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

static void vector_offset_setup(void) // so that any interrrupt does not reach th bootloader
{
    SCB_VTOR=BOOTLOADER_SIZE;
}


// gpio ---> General purpose I/O

static void gpio_setup(void)
{

    // Note: each peripheral in a an MCU like STM is off initially to save power, off means no peripheral clock is given to that component so to start first we need to need to enable the component
    rcc_periph_clock_enable(RCC_GPIOA);

    // gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);
      gpio_mode_setup(LED_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, LED_PIN); //FOR pwm mode ACCORDING TO Datasheet chart on pg 45
      gpio_set_af(LED_PORT, GPIO_AF1, LED_PIN); //AF1 is for TIM2_CH1 (TIM2 Channel 1) , pg 45 datasheet


    // for GPIO mode setup look in the docs for understanding pull and pull down device
    // Initially the LED in STM 32 is connected to A5 so we use that port and pin
    // Pull down device is set to none
}

int main(void)
{
    vector_offset_setup();
    system_setup();// from system.c
    gpio_setup();
    timer_setup();

    uint64_t start_time = system_get_ticks();
    float duty_cycle=0.0f;
    set_timer_duty_cycle(duty_cycle);

    while (1)
    {
        if (system_get_ticks() - start_time >= 100) //delay of 1sec
        {
            duty_cycle+=1.0f;
            if(duty_cycle>100.0f)
                duty_cycle=0.0f;

            set_timer_duty_cycle(duty_cycle);
            
            start_time = system_get_ticks();
        }


        //do useful work
    }
    return 0;
}