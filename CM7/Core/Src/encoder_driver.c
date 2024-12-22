/**
 * @file encoder.c
 * @brief Encoder driver implementation
 */

#include "main.h"
#include "encoder_driver.h"

float encoder_calculate_distance(uint16_t encoder_counts)
{
    // Calculate distance by dividing encoder counts by CPR and multiplying by wheel circumference

	float distance = (float)encoder_counts / (float)ENCODER_CPR * ENCODER_WHEEL_CIRCUMFERENCE_M;

    return distance;
}
