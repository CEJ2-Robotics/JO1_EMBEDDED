/**
 * @file servo.c
 * @brief Servo motor control implementation using PWM
 */

#include "main.h"
#include "servo_driver.h"

void servo_set_angle(float angle)
{
    // Check if the angle is within the valid range

    if (angle < SERVO_MIN_ANGLE || angle > SERVO_MAX_ANGLE) {
        return;
    }

    // Calculate the pulse width corresponding to the angle

    // Base pulse width is SERVO_BASE_PULSE_WIDTH_MS, adjusted based on the angle

    float pulseWidth = SERVO_BASE_PULSE_WIDTH_MS + (angle / 180.0f);

    // Get the current value of the auto-reload register for the timer (for PWM period)

    uint32_t autoreload_register_value = __HAL_TIM_GET_AUTORELOAD(&htim13);

    // Calculate the compare value based on the pulse width

    uint32_t value = (uint32_t)((pulseWidth / SERVO_PWM_PERIOD_MS) * (autoreload_register_value + 1));

    // Set the PWM duty cycle for TIM_CHANNEL_1 of Timer 13

    __HAL_TIM_SET_COMPARE(&htim13, TIM_CHANNEL_1, value);

    // Start the PWM signal generation on TIM_CHANNEL_1

    HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
}
