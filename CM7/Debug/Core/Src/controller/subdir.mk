################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/controller/robocar_c.c 

OBJS += \
./Core/Src/controller/robocar_c.o 

C_DEPS += \
./Core/Src/controller/robocar_c.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/controller/%.o Core/Src/controller/%.su Core/Src/controller/%.cyclo: ../Core/Src/controller/%.c Core/Src/controller/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H745xx -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-controller

clean-Core-2f-Src-2f-controller:
	-$(RM) ./Core/Src/controller/robocar_c.cyclo ./Core/Src/controller/robocar_c.d ./Core/Src/controller/robocar_c.o ./Core/Src/controller/robocar_c.su

.PHONY: clean-Core-2f-Src-2f-controller

