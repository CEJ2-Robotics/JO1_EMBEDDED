/**
 * @file servo_driver.h
 * @brief Servo motor control module using PWM
 * @details This module provides functions to control a servo motor by setting its angle
 *          The angle is translated into a corresponding PWM pulse width, which controls
 *          the servo's position
 *          he angle can be set within a range of -90.0 to 90.0 degrees
 */

#ifndef INC_SERVO_DRIVER_H_
#define INC_SERVO_DRIVER_H_

/* External Variables */

/** @brief Timer handle for PWM generation */

extern TIM_HandleTypeDef htim13;

/* Constants and Defines */

#define SERVO_MIN_ANGLE             -90.0f
#define SERVO_MAX_ANGLE             90.0f
#define SERVO_PWM_PERIOD_MS         20.0f
#define SERVO_BASE_PULSE_WIDTH_MS   1.5f

/* Function Prototypes */

/**
 * @brief Set the servo angle using PWM
 *
 * This function adjusts the PWM pulse width to set the servo position based on the specified
 * angle, which should be within the range of -90.0 to 90.0 degrees
 * The base pulse width is 1.5 ms, and the pulse width is adjusted proportionally to the angle
 * If the angle is out of range, the function exits without making changes
 *
 * @param angle The desired servo angle in degrees, which should be between -90.0 and 90.0
 *
 * @return None
 *
 * @note The function calculates the pulse width based on the input angle, which is
 *       added to the base pulse width
 *       The servo's position is updated using PWM, and the duty cycle is adjusted accordingly
 */

void servo_set_angle(float angle);

#endif /* INC_SERVO_DRIVER_H_ */
