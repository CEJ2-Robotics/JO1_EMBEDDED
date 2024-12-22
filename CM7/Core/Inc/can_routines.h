/**
 * @file can_routines.h
 * @brief FDCAN communication routines for encoder data
 */

#ifndef INC_CAN_ROUTINES_H_
#define INC_CAN_ROUTINES_H_

/* Configuration */

#define CAN_ENCODER_DLC         (2U)    /**< Expected encoder data length */
#define CAN_RX_BUFFER_SIZE		(64U)	/**< Size of RX buffer */

/* Status codes */

typedef enum {
    CAN_STATUS_OK = 0,
    CAN_STATUS_ERROR,
    CAN_STATUS_INVALID_LENGTH
} can_status_t;

/* Function Prototypes */

/**
 * @brief Receive encoder value via FDCAN
 * @param hfdcan Pointer to FDCAN handle
 * @param rx_header Pointer to RX header structure
 * @param encoder_value Pointer to store received encoder value
 * @return Status code indicating operation result
 */

can_status_t can_receive_encoder(FDCAN_HandleTypeDef *hfdcan,
                               FDCAN_RxHeaderTypeDef *rx_header,
                               uint16_t *encoder_value);

#endif /* INC_CAN_ROUTINES_H_ */
