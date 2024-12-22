/**
 * @file motor_driver.h
 * @brief Motor control module for speed adjustment via PWM
 * @details Provides functions to control the motor speed using PWM on Timer 14.
 *          The motor speed is set as a floating-point value between -1.0 (full reverse)
 *          and 1.0 (full forward)
 *          The module calculates the appropriate PWM duty cycle
 *          and manages PWM signal initialization and updates
 */

#ifndef INC_MOTOR_DRIVER_H_
#define INC_MOTOR_DRIVER_H_

/* External Variables */

/** @brief Timer handle for PWM generation */

extern TIM_HandleTypeDef htim14;

/* Constants and Defines */

#define MOTOR_MIN_SPEED             -1.0f
#define MOTOR_MAX_SPEED             1.0f
#define PWM_PERIOD_MS               20.0f
#define NEUTRAL_PULSE_WIDTH_MS      1.5f
#define FORWARD_PULSE_WIDTH_RANGE   0.5f
#define REVERSE_PULSE_WIDTH_RANGE   0.5f

/* Function Prototypes */

/**
 * @brief Set the motor speed using PWM.
 *
 * This function adjusts the PWM pulse width based on the input speed value,
 * which can range from -1.0 (full reverse) to 1.0 (full forward)
 * The function calculates the corresponding pulse width and updates the PWM duty cycle on
 * TIM_CHANNEL_1, starting PWM signal generation
 *
 * @param speed Desired motor speed, between -1.0 (full reverse) and 1.0 (full forward)
 *
 * @return None
 *
 * @note The function calculates the appropriate pulse width by considering
 *       the speed value and maps it to the corresponding PWM duty cycle
 */

void motor_set_speed(float speed);

#endif /* INC_MOTOR_DRIVER_H_ */
