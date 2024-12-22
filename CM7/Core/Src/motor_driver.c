/**
 * @file motor_driver.c
 * @brief Motor control implementation for PWM speed adjustment
 */

#include "main.h"
#include "motor_driver.h"

void motor_set_speed(float speed)
{
    // Ensure speed is within the valid range [-1.0, 1.0]

    if (speed < MOTOR_MIN_SPEED || speed > MOTOR_MAX_SPEED) {
        return;
    }

    // Calculate the pulse width based on the input speed value

    float pulseWidth = NEUTRAL_PULSE_WIDTH_MS + (speed > 0.0f ?
        (speed * FORWARD_PULSE_WIDTH_RANGE) :
        (speed * REVERSE_PULSE_WIDTH_RANGE));

    // Get the current auto-reload register value from Timer 14 (for PWM period)

    uint32_t autoreload_register_value = __HAL_TIM_GET_AUTORELOAD(&htim14);

    // Calculate the compare value for PWM duty cycle based on pulse width

    uint32_t value = (uint32_t)((pulseWidth / PWM_PERIOD_MS) * (autoreload_register_value + 1));

    // Set the PWM duty cycle on TIM_CHANNEL_1 of Timer 14

    __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, value);

    // Start PWM generation on TIM_CHANNEL_1

    HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
}
