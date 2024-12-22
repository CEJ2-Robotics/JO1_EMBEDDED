################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/buzzer_sound.c \
../Core/Src/can_routines.c \
../Core/Src/encoder_driver.c \
../Core/Src/freertos.c \
../Core/Src/gyro_orientation.c \
../Core/Src/imu_mpu6050.c \
../Core/Src/kalman_imu.c \
../Core/Src/kalman_pos.c \
../Core/Src/main.c \
../Core/Src/motor_driver.c \
../Core/Src/nRF24.c \
../Core/Src/servo_driver.c \
../Core/Src/stm32h7xx_hal_msp.c \
../Core/Src/stm32h7xx_hal_timebase_tim.c \
../Core/Src/stm32h7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/uart_printf.c 

OBJS += \
./Core/Src/buzzer_sound.o \
./Core/Src/can_routines.o \
./Core/Src/encoder_driver.o \
./Core/Src/freertos.o \
./Core/Src/gyro_orientation.o \
./Core/Src/imu_mpu6050.o \
./Core/Src/kalman_imu.o \
./Core/Src/kalman_pos.o \
./Core/Src/main.o \
./Core/Src/motor_driver.o \
./Core/Src/nRF24.o \
./Core/Src/servo_driver.o \
./Core/Src/stm32h7xx_hal_msp.o \
./Core/Src/stm32h7xx_hal_timebase_tim.o \
./Core/Src/stm32h7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/uart_printf.o 

C_DEPS += \
./Core/Src/buzzer_sound.d \
./Core/Src/can_routines.d \
./Core/Src/encoder_driver.d \
./Core/Src/freertos.d \
./Core/Src/gyro_orientation.d \
./Core/Src/imu_mpu6050.d \
./Core/Src/kalman_imu.d \
./Core/Src/kalman_pos.d \
./Core/Src/main.d \
./Core/Src/motor_driver.d \
./Core/Src/nRF24.d \
./Core/Src/servo_driver.d \
./Core/Src/stm32h7xx_hal_msp.d \
./Core/Src/stm32h7xx_hal_timebase_tim.d \
./Core/Src/stm32h7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/uart_printf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/buzzer_sound.cyclo ./Core/Src/buzzer_sound.d ./Core/Src/buzzer_sound.o ./Core/Src/buzzer_sound.su ./Core/Src/can_routines.cyclo ./Core/Src/can_routines.d ./Core/Src/can_routines.o ./Core/Src/can_routines.su ./Core/Src/encoder_driver.cyclo ./Core/Src/encoder_driver.d ./Core/Src/encoder_driver.o ./Core/Src/encoder_driver.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/gyro_orientation.cyclo ./Core/Src/gyro_orientation.d ./Core/Src/gyro_orientation.o ./Core/Src/gyro_orientation.su ./Core/Src/imu_mpu6050.cyclo ./Core/Src/imu_mpu6050.d ./Core/Src/imu_mpu6050.o ./Core/Src/imu_mpu6050.su ./Core/Src/kalman_imu.cyclo ./Core/Src/kalman_imu.d ./Core/Src/kalman_imu.o ./Core/Src/kalman_imu.su ./Core/Src/kalman_pos.cyclo ./Core/Src/kalman_pos.d ./Core/Src/kalman_pos.o ./Core/Src/kalman_pos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/motor_driver.cyclo ./Core/Src/motor_driver.d ./Core/Src/motor_driver.o ./Core/Src/motor_driver.su ./Core/Src/nRF24.cyclo ./Core/Src/nRF24.d ./Core/Src/nRF24.o ./Core/Src/nRF24.su ./Core/Src/servo_driver.cyclo ./Core/Src/servo_driver.d ./Core/Src/servo_driver.o ./Core/Src/servo_driver.su ./Core/Src/stm32h7xx_hal_msp.cyclo ./Core/Src/stm32h7xx_hal_msp.d ./Core/Src/stm32h7xx_hal_msp.o ./Core/Src/stm32h7xx_hal_msp.su ./Core/Src/stm32h7xx_hal_timebase_tim.cyclo ./Core/Src/stm32h7xx_hal_timebase_tim.d ./Core/Src/stm32h7xx_hal_timebase_tim.o ./Core/Src/stm32h7xx_hal_timebase_tim.su ./Core/Src/stm32h7xx_it.cyclo ./Core/Src/stm32h7xx_it.d ./Core/Src/stm32h7xx_it.o ./Core/Src/stm32h7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/uart_printf.cyclo ./Core/Src/uart_printf.d ./Core/Src/uart_printf.o ./Core/Src/uart_printf.su

.PHONY: clean-Core-2f-Src

