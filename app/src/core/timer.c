#include "core/timer.h"
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/rcc.h>

#define PRESCALER (84)
#define ARR_VALUE (1000)

//freq = system_freq/((prescaler-1)*(arr-1))  , arr is auto reload reg.

void timer_setup(void){

    rcc_periph_clock_enable(RCC_TIM2);//why TIM2 bcuz in datasheet it is common to GPIO A5 pg no 45 datasheet

    //high level timer config
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    //setup pwm mode
    timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1); //setup PWM  , OC! is output Channel 1

    //enable PWM output
    timer_enable_counter(TIM2);
    timer_enable_oc_output(TIM2, TIM_OC1);

    //set frequency and resolution
    timer_set_prescaler(TIM2, PRESCALER-1);
    timer_set_period(TIM2, ARR_VALUE-1);

};
void set_timer_duty_cycle(float duty_cycle){


    const float raw_value = (float)ARR_VALUE * (duty_cycle/100.0f);
    timer_set_oc_value(TIM1, TIM_OC1, (uint32_t)raw_value);
};