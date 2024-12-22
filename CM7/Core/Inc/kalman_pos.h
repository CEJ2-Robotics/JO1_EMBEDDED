/*
 * kalman_pos.h
 */

#ifndef INC_KALMAN_POS_H_
#define INC_KALMAN_POS_H_

#include "common_types.h"

/* Structures */

/**
 * @brief State structure representing the system's position and orientation
 * @note All values are in their respective units (e.g., meters for position, degrees for angle)
 */

typedef struct {
    float x;       /**< X-coordinate of the state (in meters) */
    float y;       /**< Y-coordinate of the state (in meters) */
    float angle;   /**< Orientation angle of the state (in degrees) */
} state_t;

/**
 * @brief Kalman filter structure for state estimation
 *
 * This structure encapsulates the state, covariance matrix, and noise covariances
 * required for implementing a Kalman filter for sensor fusion and state prediction
 */

typedef struct {
    float P[3][3];     /**< Covariance matrix representing uncertainty in the state */
    state_t state;     /**< Current estimated state of the system */
    float Q[3][3];     /**< Process noise covariance matrix */
    float R[3][3];     /**< Measurement noise covariance matrix */
} kalman_filter_t;

/* Function Protoypes */

/**
 * @brief Initializes the Kalman filter
 *
 * @param kf Pointer to the Kalman filter structure
 * @param x Initial x-coordinate of the state
 * @param y Initial y-coordinate of the state
 * @param angle Initial orientation angle of the state (in degrees)
 */

void kalman_init(kalman_filter_t *kf, float x, float y, float angle);

/**
 * @brief Performs the prediction step of the Kalman filter.
 *
 * @param kf Pointer to the Kalman filter structure
 * @param encoder_distance Distance traveled (from encoder data, in meters)
 * @param imu_angle Current orientation angle (from IMU, in degrees)
 */

void kalman_predict(kalman_filter_t *kf, float encoder_distance, float imu_angle);
void kalman_update(kalman_filter_t *kf, vehicle_coordinates_t camera_coords);

#endif /* INC_KALMAN_POS_H_ */
