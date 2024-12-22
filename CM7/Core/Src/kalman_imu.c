/**
 * @file kalman_imu.c
 * @brief Implementation of Kalman Filter for the IMU measurements
 */

#include "main.h"
#include "imu_mpu6050.h"
#include "kalman_imu.h"

void imu_kalman_init(imu_kalman_filter_t *kf, float processNoise, float measurementNoise, float initialValue)
{
    kf->q = processNoise;
    kf->r = measurementNoise;
    kf->x = initialValue;
    kf->p = 1.0f; 				// Set initial estimation error covariance
    kf->k = 0.0f; 				// Set initial Kalman gain
}

float imu_kalman_update(imu_kalman_filter_t *kf, float measurement)
{
    // Prediction update

    kf->p = kf->p + kf->q;		// Update the estimation error covariance

    // Measurement update

    kf->k = kf->p / (kf->p + kf->r);           		// Calculate the Kalman gain
    kf->x = kf->x + kf->k * (measurement - kf->x); 	// Update the state estimate with the new measurement
    kf->p = (1.0f - kf->k) * kf->p;           		// Update the estimation error covariance

    return kf->x;				// Return the updated state estimate (filtered sensor value)
}
