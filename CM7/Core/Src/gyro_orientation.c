/**
 * @file gyro_orientation.c
 * @brief Implementation of gyroscope-based orientation tracking
 */

#include "main.h"
#include "gyro_orientation.h"

void gyro_orient_init(gyro_orient_state_t* state)
{
    if (state != NULL) {
    	state->yaw_angle = 0.0f;
        state->prev_yaw_rate = 0.0f;
        state->prev_timestamp = 0;
    }
}

float gyro_orient_update(gyro_orient_state_t* state,
                        const imu_data_t* imu_data,
                        uint32_t timestamp)
{
    if (state == NULL || imu_data == NULL) {
        return 0.0f;
    }

    // Calculate time delta in seconds

    float delta_time = (float)(timestamp - state->prev_timestamp) / GYRO_ORIENT_MS_TO_S;

    // Integrate yaw rate using trapezoidal method

    float yaw_change = 0.5f * (state->prev_yaw_rate + imu_data->gz) * delta_time;

    // Update cumulative yaw angle

    state->yaw_angle += yaw_change;

    // Normalize angle to 0-360 range

    if (state->yaw_angle < GYRO_ORIENT_MIN_DEG) {
        state->yaw_angle += GYRO_ORIENT_MAX_DEG;
    } else if (state->yaw_angle >= GYRO_ORIENT_MAX_DEG) {
        state->yaw_angle -= GYRO_ORIENT_MAX_DEG;
    }

    // Store current values for next iteration

    state->prev_yaw_rate = imu_data->gz;
    state->prev_timestamp = timestamp;

    return state->yaw_angle;
}
