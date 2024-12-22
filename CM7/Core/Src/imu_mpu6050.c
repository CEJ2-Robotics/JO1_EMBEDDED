/**
 * @file imu_mpu6050.c
 * @brief Implementation of HAL for MPU6050 IMU sensor
 */

#include "main.h"
#include "imu_mpu6050.h"
#include "kalman_imu.h"
#include "uart_printf.h"

/* Global Variables */

static uint8_t mpu_6050_addr;
static float tau_val, dt_val;
static float aScaleFactor, gScaleFactor;

RawData rawData;
AccelOffset accelOffset;
GyroOffset gyroOffset;
Attitude attitude;

static imu_kalman_filter_t kf_ax, kf_ay, kf_az;
static imu_kalman_filter_t kf_gx, kf_gy, kf_gz;

/* Functions */

void imu_setup_routine(I2C_HandleTypeDef *I2Cx)
{
	imu_init(I2Cx, AD0_LOW, AFSR_2G, GFSR_250DPS, IMU_DEFAULT_COMP_TAU, IMU_DEFAULT_SAMPLE_TIME);

    // Initialize Kalman filters

    // Lower process noise for gyroscope, moderate measurement noise

    imu_kalman_init(&kf_gx, KF_GYRO_PROCESS_NOISE, KF_GYRO_MEASURE_NOISE, KF_GYRO_INIT_VALUE);
    imu_kalman_init(&kf_gy, KF_GYRO_PROCESS_NOISE, KF_GYRO_MEASURE_NOISE, KF_GYRO_INIT_VALUE);
    imu_kalman_init(&kf_gz, KF_GYRO_PROCESS_NOISE, KF_GYRO_MEASURE_NOISE, KF_GYRO_INIT_VALUE);

	// Slightly more process noise for accelerometer, higher measurement noise

    imu_kalman_init(&kf_ax, KF_ACCEL_PROCESS_NOISE, KF_ACCEL_MEASURE_NOISE, KF_ACCEL_INIT_VALUE);
    imu_kalman_init(&kf_ay, KF_ACCEL_PROCESS_NOISE, KF_ACCEL_MEASURE_NOISE, KF_ACCEL_INIT_VALUE);
    imu_kalman_init(&kf_az, KF_ACCEL_PROCESS_NOISE, KF_ACCEL_MEASURE_NOISE, KF_ACCEL_INIT_VALUE);
}

void imu_init(I2C_HandleTypeDef *I2Cx, uint8_t addr, uint8_t aScale, uint8_t gScale, float tau, float dt)
{
    uint8_t select = 0;

    // Save values

    mpu_6050_addr = addr << 1;
    tau_val = tau;
    dt_val = dt;

    HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(I2Cx, (mpu_6050_addr + 0), 1, MPU6050_I2C_TIMEOUT_MS);

    if (ret == HAL_OK) {
        printf("THE DEVICE IS OK\n\r");
    }
    else {
        printf("THE DEVICE IS NOT READY\n\r");
    }

    // Quit sleep mode and enable temperature sensor

    select = 0x00;

    ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_PWR_MGMT_1, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);

    if (ret == HAL_OK) {
        printf("OUT OF SLEEP MODE AND TEMPERATURE SENSOR ON IS OK\n\r");
    }
    else {
        printf("SLEEP MODE AND TEMPERATURE SENSOR ERROR\n\r");
    }

    // Set the full scale ranges

    ret = imu_write_accel_full_scale_range(I2Cx, aScale);

    if (ret == HAL_OK) {
        printf("ACCELEROMETER SCALE IS OK\n\r");
    }
    else {
        printf("ACCELEROMETER SCALE NOT READY\n\r");
    }

    ret = imu_write_gyro_full_scale_range(I2Cx, gScale);

    if (ret == HAL_OK) {
        printf("GYROSCOPE SCALE IS OK\n\r");
    }
    else {
        printf("GYROSCOPE SCALE NOT READY\n\r");
    }

    // Calibrate the accelerometer and the gyroscope

    imu_calibrate_accel(I2Cx, IMU_CAL_SAMPLES);
    imu_calibrate_gyro(I2Cx, IMU_CAL_SAMPLES);
}

void imu_calibrate_gyro(I2C_HandleTypeDef *I2Cx, uint16_t numCalPoints)
{
    int32_t sum_gx = 0, sum_gy = 0, sum_gz = 0;

    for (uint16_t i = 0; i < numCalPoints; i++)
    {
        imu_read_raw_data(I2Cx);

        sum_gx += rawData.gx;
        sum_gy += rawData.gy;
        sum_gz += rawData.gz;

        HAL_Delay(MPU6050_CAL_DELAY_MS);
    }

    gyroOffset.x = (sum_gx / numCalPoints);
    gyroOffset.y = (sum_gy / numCalPoints);
    gyroOffset.z = (sum_gz / numCalPoints);		// Gravity compensation
}

void imu_calibrate_accel(I2C_HandleTypeDef *I2Cx, uint16_t numCalPoints)
{
    int32_t sum_ax = 0, sum_ay = 0, sum_az = 0;

    for (uint16_t i = 0; i < numCalPoints; i++)
    {
        imu_read_raw_data(I2Cx);

        sum_ax += rawData.ax;
        sum_ay += rawData.ay;
        sum_az += rawData.az;

        HAL_Delay(MPU6050_CAL_DELAY_MS);
    }

    accelOffset.x = (sum_ax / numCalPoints);
    accelOffset.y = (sum_ay / numCalPoints);
    accelOffset.z = (sum_az / numCalPoints);	// Gravity compensation
}

void imu_read_raw_data(I2C_HandleTypeDef *I2Cx)
{
    // Initialization buffer

    uint8_t buf[14];

    // Subroutine for reading the raw data

    HAL_I2C_Mem_Read(I2Cx, (mpu_6050_addr + 1), MPU6050_ACCEL_XOUT_H, 1, buf, 14, MPU6050_I2C_TIMEOUT_MS);

    // Bit shift the data

    rawData.ax = buf[0] << 8 | buf[1];
    rawData.ay = buf[2] << 8 | buf[3];
    rawData.az = buf[4] << 8 | buf[5];
    rawData.gx = buf[8] << 8 | buf[9];
    rawData.gy = buf[10] << 8 | buf[11];
    rawData.gz = buf[12] << 8 | buf[13];
}

imu_data_t imu_read_processed_data(I2C_HandleTypeDef *I2Cx)
{
	imu_data_t imu_data;

    // Get raw values from the IMU

    imu_read_raw_data(I2Cx);

    // Compensate for accelerometer offset

    imu_data.ax = (rawData.ax - accelOffset.x) * (MPU6050_GRAVITY_EARTH / aScaleFactor);
    imu_data.ay = (rawData.ay - accelOffset.y) * (MPU6050_GRAVITY_EARTH / aScaleFactor);
    imu_data.az = (rawData.az - accelOffset.z) * (MPU6050_GRAVITY_EARTH / aScaleFactor);

    // Compensate for gyroscope offset

    imu_data.gx = (rawData.gx - gyroOffset.x) / gScaleFactor;
    imu_data.gy = (rawData.gy - gyroOffset.y) / gScaleFactor;
    imu_data.gz = (rawData.gz - gyroOffset.z) / gScaleFactor;

    // Apply Kalman filter to each axis

    imu_data.ax = imu_kalman_update(&kf_ax, imu_data.ax);
    imu_data.ay = imu_kalman_update(&kf_ay, imu_data.ay);
    imu_data.az = imu_kalman_update(&kf_az, imu_data.az);

    imu_data.gx = imu_kalman_update(&kf_gx, imu_data.gx);
    imu_data.gy = imu_kalman_update(&kf_gy, imu_data.gy);
    imu_data.gz = imu_kalman_update(&kf_gz, imu_data.gz);

    return imu_data;
}

HAL_StatusTypeDef imu_write_gyro_full_scale_range(I2C_HandleTypeDef *I2Cx, uint8_t gScale)
{
    // Variable initialization

    uint8_t select;
    HAL_StatusTypeDef ret = HAL_OK;

    // Set the value

    switch (gScale) {
		case GFSR_250DPS:
			gScaleFactor = 131.0;
			select = 0x00;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_GYRO_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
		case GFSR_500DPS:
			gScaleFactor = 65.5;
			select = 0x08;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_GYRO_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
		case GFSR_1000DPS:
			gScaleFactor = 32.8;
			select = 0x10;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_GYRO_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
		case GFSR_2000DPS:
			gScaleFactor = 16.4;
			select = 0x18;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_GYRO_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
		default:
			gScaleFactor = 131.0;
			select = 0x00;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_GYRO_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
    }

    return ret;
}

HAL_StatusTypeDef imu_write_accel_full_scale_range(I2C_HandleTypeDef *I2Cx, uint8_t aScale)
{
    // Variable initialization

    uint8_t select;
    HAL_StatusTypeDef ret = HAL_OK;

    // Set the value

    switch (aScale) {

		case AFSR_2G:
			aScaleFactor = 16384.0;
			select = 0x00;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_ACCEL_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
		case AFSR_4G:
			aScaleFactor = 8192.0;
			select = 0x08;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_ACCEL_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
		case AFSR_8G:
			aScaleFactor = 4096.0;
			select = 0x10;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_ACCEL_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
		case AFSR_16G:
			aScaleFactor = 2048.0;
			select = 0x18;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_ACCEL_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
		default:
			aScaleFactor = 16384.0;
			select = 0x00;
			ret = HAL_I2C_Mem_Write(I2Cx, (mpu_6050_addr + 0), MPU6050_ACCEL_CONFIG, 1, &select, 1, MPU6050_I2C_TIMEOUT_MS);
			break;
    }

    return ret;
}
