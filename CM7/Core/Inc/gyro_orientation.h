/**
 * @file gyro_orientation.h
 * @brief Gyroscope-based orientation tracking module
 * @note Uses trapezoidal integration of gyroscope readings
 */

#ifndef INC_GYRO_ORIENTATION_H_
#define INC_GYRO_ORIENTATION_H_

#include "common_types.h"

/* Configuration */

#define GYRO_ORIENT_MAX_DEG     (360.0f)
#define GYRO_ORIENT_MIN_DEG     (0.0f)
#define GYRO_ORIENT_MS_TO_S     (1000.0f)

/* Types */

typedef struct {
    float     yaw_angle;
    float     prev_yaw_rate;
    uint32_t  prev_timestamp;
} gyro_orient_state_t;

/* Function prototypes */

/**
 * @brief Initialize orientation tracking state
 * @param state Pointer to state structure
 * @return None
 */

void gyro_orient_init(gyro_orient_state_t* state);

/**
 * @brief Update yaw orientation based on gyroscope data
 * @param state Pointer to state structure
 * @param imu_data Current IMU sensor readings
 * @param timestamp Current system timestamp in milliseconds
 * @return Current yaw angle in degrees [0-360]
 */

float gyro_orient_update(gyro_orient_state_t* state,
                        const imu_data_t* imu_data,
                        uint32_t timestamp);

#endif /* INC_GYRO_ORIENTATION_H_ */
