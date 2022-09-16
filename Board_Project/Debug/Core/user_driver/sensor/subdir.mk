################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/user_driver/sensor/sensor_base_process.c \
../Core/user_driver/sensor/sensor_knock.c \
../Core/user_driver/sensor/sensor_rpm.c 

C_DEPS += \
./Core/user_driver/sensor/sensor_base_process.d \
./Core/user_driver/sensor/sensor_knock.d \
./Core/user_driver/sensor/sensor_rpm.d 

OBJS += \
./Core/user_driver/sensor/sensor_base_process.o \
./Core/user_driver/sensor/sensor_knock.o \
./Core/user_driver/sensor/sensor_rpm.o 


# Each subdirectory must supply rules for building sources it contributes
Core/user_driver/sensor/sensor_base_process.o: ../Core/user_driver/sensor/sensor_base_process.c Core/user_driver/sensor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L151xBA -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../Core/user_driver -I../Core/user_driver/ble_com -I../Core/user_driver/extern_flash -I../Core/user_driver/peripheral -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/user_driver/shell -I../Core/user_driver/sensor -I../Core/user_driver/vsm_service -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -MMD -MP -MF"Core/user_driver/sensor/sensor_base_process.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/user_driver/sensor/sensor_knock.o: ../Core/user_driver/sensor/sensor_knock.c Core/user_driver/sensor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L151xBA -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../Core/user_driver -I../Core/user_driver/ble_com -I../Core/user_driver/extern_flash -I../Core/user_driver/peripheral -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/user_driver/shell -I../Core/user_driver/sensor -I../Core/user_driver/vsm_service -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -MMD -MP -MF"Core/user_driver/sensor/sensor_knock.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/user_driver/sensor/sensor_rpm.o: ../Core/user_driver/sensor/sensor_rpm.c Core/user_driver/sensor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L151xBA -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../Core/user_driver -I../Core/user_driver/ble_com -I../Core/user_driver/extern_flash -I../Core/user_driver/peripheral -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/user_driver/shell -I../Core/user_driver/sensor -I../Core/user_driver/vsm_service -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -MMD -MP -MF"Core/user_driver/sensor/sensor_rpm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

