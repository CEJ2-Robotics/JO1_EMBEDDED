/**
 * @file can_routines.c
 * @brief Implementation of FDCAN communication routines
 */

#include "main.h"
#include "can_routines.h"

can_status_t can_receive_encoder(FDCAN_HandleTypeDef *hfdcan,
                               FDCAN_RxHeaderTypeDef *rx_header,
                               uint16_t *encoder_value)
{
    uint8_t rx_data[CAN_RX_BUFFER_SIZE];

    // Validate parameters

    if (hfdcan == NULL || rx_header == NULL || encoder_value == NULL) {
        return CAN_STATUS_ERROR;
    }

    // Attempt to get message from FIFO0

    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, rx_header, rx_data) != HAL_OK) {
        return CAN_STATUS_ERROR;
    }

    // Check data length

    uint8_t data_length = (rx_header->DataLength >> 16) & 0x0F;

    if (data_length != CAN_ENCODER_DLC) {
        return CAN_STATUS_INVALID_LENGTH;
    }

    // Combine bytes into encoder value

    *encoder_value = (uint16_t)((rx_data[1] << 8) | rx_data[0]);

    return CAN_STATUS_OK;
}
