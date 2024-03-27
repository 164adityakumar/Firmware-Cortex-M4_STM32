#include "core/system.h"
#include <libopencm3/cm3/systick.h>
#include <libopencm3/cm3/vector.h>
#include <libopencm3/stm32/rcc.h>


volatile uint64_t ticks = 0; // volatile is used to tell the compiler that the variable can be changed by the interrupt for more detail look in notion docs
// why a 64 bit tick in a 32 bit MCU? ----> notion docs

void sys_tick_handler(void)
{
    ticks++;
    // as the ticks is 64 bits so it takes 2 asm instructions to increment the value in 32 bit mcu so an interrupt can occur in between the 2 instructions so the most simple way to avoid is to mask the interrupts for the meantime of incrementing the value
}

uint64_t system_get_ticks(void)
{
    return ticks;
}

static void rcc_setup(void)
{
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
    // 84MHz is the max frequency it can attain

    //  RCC----> Reset and clock controller
    //  using this function we setup the clock frequency of the whole system 4
    //  pll----> phase locked loop
    //  hsi----> high speed internal clock
}

static void systick_setup(void)
{
    systick_set_frequency(SYSTICK_FREQ, CPU_FREQ);
    // 1000 is the frequency of the systick timer
    // 84000000 is the clock frequency of the system our device stm32
    // systick timer is used to give delay in the system
    // 1ms delay is given by this timer
    systick_counter_enable();
    systick_interrupt_enable(); // enabling interrupt
    // SysTick is a simple timer that is part of the NVIC controller in the Cortex-M microprocessor.
    //  Its intended purpose is to provide a periodic interrupt for an RTOS, but it can be used for other simple timing purposes.
    // NVIC stands for Nested Vectored Interrupt Controller
}

void system_setup(void)
{
    rcc_setup();
    systick_setup();
}