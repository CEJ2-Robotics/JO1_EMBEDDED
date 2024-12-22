/**
 * @file imu_mpu6050.h
 * @brief Hardware abstraction layer for MPU6050 6-axis motion tracking device
 * @details Provides initialization, configuration and data acquisition
 *          functions for the MPU6050 IMU sensor
 *          The device combines a 3-axis gyroscope and 3-axis accelerometer
 */

#ifndef INC_IMU_MPU6050_H_
#define INC_IMU_MPU6050_H_

#include "common_types.h"

/* Physical constants */

#define RAD2DEG						57.2957795131

/* MPU6050 Register Map */

#define MPU6050_PWR_MGMT_1			0x6B
#define MPU6050_GYRO_CONFIG			0x1B
#define MPU6050_ACCEL_CONFIG		0x1C
#define MPU6050_ACCEL_XOUT_H		0x3B

/* Device Identification */

#define WHO_AM_I					0x75
#define WHO_AM_I_6050_ANS			0x68

/* Device Configuration */

#define MPU6050_I2C_TIMEOUT_MS		1000
#define MPU6050_GRAVITY_EARTH     	9.81f
#define MPU6050_CAL_DELAY_MS      	10

/* I2C Address Options */

#define AD0_LOW						0x68
#define AD0_HIGH					0x69

/* Default Configuration */

#define IMU_DEFAULT_COMP_TAU     	0.98f
#define IMU_DEFAULT_SAMPLE_TIME  	0.004f
#define IMU_CAL_SAMPLES          	100

/* Kalman Filter Parameters */

#define KF_ACCEL_PROCESS_NOISE    	0.05f
#define KF_ACCEL_MEASURE_NOISE    	0.50f
#define KF_ACCEL_INIT_VALUE       	0.0f

#define KF_GYRO_PROCESS_NOISE     	0.01f
#define KF_GYRO_MEASURE_NOISE     	0.30f
#define KF_GYRO_INIT_VALUE        	0.0f

/* Full scale ranges */

enum gyroscopeFullScaleRange {
    GFSR_250DPS,
    GFSR_500DPS,
    GFSR_1000DPS,
    GFSR_2000DPS
};

enum accelerometerFullScaleRange {
    AFSR_2G,
    AFSR_4G,
    AFSR_8G,
    AFSR_16G
};

/* Structures */

typedef struct {
    int16_t ax, ay, az, gx, gy, gz;
} RawData;

typedef struct {
    float x, y, z;
} AccelOffset;

typedef struct {
    float x, y, z;
} GyroOffset;

typedef struct {
    float r, p, y;
} Attitude;

/* Function prototypes */

/**
 * @brief Initialize IMU and Kalman filters with default settings
 * @param I2Cx Pointer to I2C handle structure
 * @return None
 *
 * @note Initializes 6 Kalman filters: 3 for accelerometer (ax,ay,az) and 3 for gyroscope (gx,gy,gz)
 *       with noise parameters
 */

void imu_setup_routine(I2C_HandleTypeDef *I2Cx);

/**
 * @brief Initialize and configure the MPU6050 sensor
 * @param I2Cx Pointer to I2C handle structure
 * @param addr I2C address (AD0_LOW or AD0_HIGH)
 * @param aScale Accelerometer full-scale range (AFSR_2G, AFSR_4G, AFSR_8G, AFSR_16G)
 * @param gScale Gyroscope full-scale range (GFSR_250DPS, GFSR_500DPS, GFSR_1000DPS, GFSR_2000DPS)
 * @param tau Complementary filter time constant
 * @param dt Sample time interval in seconds
 * @return None
 */

void imu_init(I2C_HandleTypeDef *I2Cx, uint8_t addr, uint8_t aScale, uint8_t gScale, float tau, float dt);

/**
 * @brief Calibrate gyroscope by calculating offset values
 * @param I2Cx Pointer to I2C handle structure
 * @param numCalPoints Number of samples to use for calibration
 * @return None
 *
 * @note Takes multiple readings and averages them to determine gyroscope offset
 *       Uses 10ms delay between readings
 */

void imu_calibrate_gyro(I2C_HandleTypeDef *I2Cx, uint16_t numCalPoints);

/**
 * @brief Calibrate accelerometer by calculating offset values
 * @param I2Cx Pointer to I2C handle structure
 * @param numCalPoints Number of samples to use for calibration
 * @return None
 *
 * @note Takes multiple readings and averages them to determine accelerometer offset
 *       Uses 10ms delay between readings
 */

void imu_calibrate_accel(I2C_HandleTypeDef *I2Cx, uint16_t numCalPoints);

/**
 * @brief Read raw sensor data from MPU6050
 * @param I2Cx Pointer to I2C handle structure
 * @return None
 *
 * @note Reads 14 bytes of data starting from ACCEL_XOUT_H register
 *       Updates rawData structure with accelerometer and gyroscope values
 */

void imu_read_raw_data(I2C_HandleTypeDef *I2Cx);

/**
 * @brief Process and filter raw sensor data
 * @param I2Cx Pointer to I2C handle structure
 * @return imu_data_t Processed and filtered sensor data
 *
 * @note Applies offset compensation, scaling, and Kalman filtering
 *       Accelerometer data is converted to m/s^2
 *       Gyroscope data is converted to degrees/s
 */

imu_data_t imu_read_processed_data(I2C_HandleTypeDef *I2Cx);

/**
 * @brief Configure gyroscope full-scale range
 * @param I2Cx Pointer to I2C handle structure
 * @param gScale Desired full-scale range (GFSR_250DPS, GFSR_500DPS, GFSR_1000DPS, GFSR_2000DPS)
 * @return HAL_StatusTypeDef HAL status
 *
 * @note Updates gScaleFactor according to selected range
 *       Default range is ±250 degrees/second if invalid scale is provided
 */

HAL_StatusTypeDef imu_write_gyro_full_scale_range(I2C_HandleTypeDef *I2Cx, uint8_t gScale);

/**
 * @brief Configure accelerometer full-scale range
 * @param I2Cx Pointer to I2C handle structure
 * @param aScale Desired full-scale range (AFSR_2G, AFSR_4G, AFSR_8G, AFSR_16G)
 * @return HAL_StatusTypeDef HAL status
 *
 * @note Updates aScaleFactor according to selected range
 *       Default range is ±2g if invalid scale is provided
 */

HAL_StatusTypeDef imu_write_accel_full_scale_range(I2C_HandleTypeDef *I2Cx, uint8_t aScale);

#endif /* INC_IMU_MPU6050_H_ */
