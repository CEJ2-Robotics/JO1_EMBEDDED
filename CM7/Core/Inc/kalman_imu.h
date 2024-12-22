/**
 * @file kalman_imu.h
 * @brief Kalman Filter applied to IMU sensor measurements
 * @details Provides the initialization and update functions for the Kalman Filter,
 *          which is used to estimate the state of an IMU system
 *          The Kalman Filter is applied to process accelerometer and gyroscope data, helping to
 *          estimate accurate sensor readings despite the noisy nature of real-world measurements
 */

#ifndef INC_KALMAN_IMU_H_
#define INC_KALMAN_IMU_H_

/* Kalman Filter Structure */

/**
 * @brief Structure to hold Kalman filter parameters
 *
 * This structure contains the parameters used in the Kalman Filter:
 *   - `q`: Process noise covariance (uncertainty in the process model)
 *   - `r`: Measurement noise covariance (uncertainty in the measurements)
 *   - `x`: The current estimate of the state
 *   - `p`: Estimation error covariance (uncertainty in the estimate)
 *   - `k`: Kalman gain (weight given to the new measurement vs the prediction)
 */

typedef struct {
    float q;      /**< Process noise covariance */
    float r;      /**< Measurement noise covariance */
    float x;      /**< Estimated state */
    float p;      /**< Estimation error covariance */
    float k;      /**< Kalman gain */
} imu_kalman_filter_t;

/* Function Prototypes */

/**
 * @brief Initialize the Kalman Filter for IMU data with process noise, measurement noise, and initial estimate
 * @param kf Pointer to the Kalman Filter structure
 * @param processNoise Process noise covariance (q)
 * @param measurementNoise Measurement noise covariance (r)
 * @param initialValue Initial estimate of the state (e.g., initial sensor reading)
 * @return None
 *
 * @note Initializes the Kalman Filter for use with IMU data, setting up the filter with the provided noise parameters
 *       and initial state estimate. The estimation error covariance (`p`) is set to 1.0, and the Kalman gain (`k`)
 *       is initialized to zero
 */

void imu_kalman_init(imu_kalman_filter_t *kf, float processNoise, float measurementNoise, float initialValue);

/**
 * @brief Update the Kalman Filter with a new measurement from the IMU sensor and returns the filtered state estimate
 * @param kf Pointer to the Kalman Filter structure
 * @param measurement New sensor measurement (e.g., accelerometer or gyroscope data) to update the state estimate
 * @return The updated state estimate (e.g., filtered sensor reading)
 *
 * @note This function performs the prediction and measurement update steps of the Kalman Filter algorithm.
 *       It calculates the new estimate based on the previous estimate and the new IMU sensor measurement,
 *       and it helps to reduce noise in the IMU sensor data
 */

float imu_kalman_update(imu_kalman_filter_t *kf, float measurement);

#endif /* INC_KALMAN_IMU_H_ */
