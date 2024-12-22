/**
 * @file encoder_driver.h
 * @brief Encoder driver
 * @details This module handles quadrature encoder measurements and calculations
 *          for wheel distance tracking
 */

#ifndef INC_ENCODER_DRIVER_H_
#define INC_ENCODER_DRIVER_H_

/* Physical and hardware constants */

#define ENCODER_WHEEL_RADIUS_M			(0.034f)	/**< Wheel radius in meters */
#define ENCODER_CPR						(210U)		/**< Encoder counts per revolution */
#define ENCODER_PI						(3.14159f)	/**< PI constant */

#define ENCODER_WHEEL_CIRCUMFERENCE_M 	(2.0f * ENCODER_PI * ENCODER_WHEEL_RADIUS_M)

/* Function prototypes */

/**
 * @brief Calculate distance from encoder counts
 * @param encoder_counts Current encoder count value
 * @return Distance in meters
 */

float encoder_calculate_distance(uint16_t encoder_counts);

#endif /* INC_ENCODER_DRIVER_H_ */
