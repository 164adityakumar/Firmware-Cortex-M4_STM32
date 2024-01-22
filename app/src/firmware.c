#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED_PORT (GPIOA)
#define LED_PIN (GPIO5)

static void rcc_setup(void)
{
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]);
    // 84MHz is the max frequency it can attain

    //  RCC----> Reset and clock controller
    //  using this function we setup the clock frequency of the whole system 4
    //  pll----> phase locked loop
    //  hsi----> high speed internal clock 
}

// gpio ---> General purpose I/O  

static void gpio_setup(void)
{

    // Note: each peripheral in a an MCU like STM is off initially to save power, off means no peripheral clock is given to that component so to start first we need to need to enable the component
    rcc_periph_clock_enable(RCC_GPIOA); 

    gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);

    // for GPIO mode setup look in the docs for understanding pull and pull down device 
    // Initially the LED in STM 32 is connected to A5 so we use that port and pin
    // Pull down device is set to none 
}

static void delay_cycles(uint32_t cycles){
    for(uint32_t i=0;i<cycles;i++)
    {
        __asm__("nop"); // adding assembly to give delay ( leaving the loop empty won't give any delay)
    }
}

int main(void)
{

    rcc_setup();
    gpio_setup();

    while (   1)
    {
           gpio_toggle(LED_PORT,LED_PIN);
           delay_cycles(84000000/4); // Adding delay to see the blinking
    }
    return 0;
}