################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/user_driver/peripheral/adc_driver.c \
../Core/user_driver/peripheral/timer_driver.c \
../Core/user_driver/peripheral/uart_com.c 

C_DEPS += \
./Core/user_driver/peripheral/adc_driver.d \
./Core/user_driver/peripheral/timer_driver.d \
./Core/user_driver/peripheral/uart_com.d 

OBJS += \
./Core/user_driver/peripheral/adc_driver.o \
./Core/user_driver/peripheral/timer_driver.o \
./Core/user_driver/peripheral/uart_com.o 


# Each subdirectory must supply rules for building sources it contributes
Core/user_driver/peripheral/adc_driver.o: ../Core/user_driver/peripheral/adc_driver.c Core/user_driver/peripheral/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L151xBA -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../Core/user_driver -I../Core/user_driver/ble_com -I../Core/user_driver/extern_flash -I../Core/user_driver/peripheral -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/user_driver/shell -I../Core/user_driver/sensor -I../Core/user_driver/vsm_service -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -MMD -MP -MF"Core/user_driver/peripheral/adc_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/user_driver/peripheral/timer_driver.o: ../Core/user_driver/peripheral/timer_driver.c Core/user_driver/peripheral/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L151xBA -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../Core/user_driver -I../Core/user_driver/ble_com -I../Core/user_driver/extern_flash -I../Core/user_driver/peripheral -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/user_driver/shell -I../Core/user_driver/sensor -I../Core/user_driver/vsm_service -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -MMD -MP -MF"Core/user_driver/peripheral/timer_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/user_driver/peripheral/uart_com.o: ../Core/user_driver/peripheral/uart_com.c Core/user_driver/peripheral/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L151xBA -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I../Core/user_driver -I../Core/user_driver/ble_com -I../Core/user_driver/extern_flash -I../Core/user_driver/peripheral -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/user_driver/shell -I../Core/user_driver/sensor -I../Core/user_driver/vsm_service -O0 -ffunction-sections -fdata-sections -Wall -u _printf_float -fstack-usage -MMD -MP -MF"Core/user_driver/peripheral/uart_com.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

