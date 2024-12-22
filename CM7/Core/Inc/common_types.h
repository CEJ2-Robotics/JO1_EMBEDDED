/**
 * @file common_types.h
 * @brief Common data types shared across modules
 */

#ifndef INC_COMMON_TYPES_H_
#define INC_COMMON_TYPES_H_

#include <stdint.h>

/**
 * @brief IMU sensor data structure
 * @note All values are in their respective SI units
 */

typedef struct {

    // Accelerometer data in m/s^2

    float ax;		/**< Accelerometer X-axis acceleration */
    float ay;		/**< Accelerometer Y-axis acceleration */
    float az;		/**< Accelerometer Z-axis acceleration */

    // Gyroscope data in degrees/second

    float gx;		/**< Gyroscope X-axis angular rate */
    float gy;		/**< Gyroscope Y-axis angular rate */
    float gz;		/**< Gyroscope Z-axis angular rate */

} imu_data_t;

/**
 * @brief Vehicle coordinates structure
 * @note This structure contains the coordinates and orientation of the vehicle
 */

typedef struct
{
    uint16_t x;			/**< X-coordinate of the vehicle */
    uint16_t y;			/**< Y-coordinate of the vehicle */
    uint16_t angle;		/**< Orientation angle of the vehicle (in degrees) */
} vehicle_coordinates_t;

#endif /* INC_COMMON_TYPES_H_ */
