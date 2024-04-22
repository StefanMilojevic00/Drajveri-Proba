################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/AirQualityIndicator.c \
../Core/Src/AlarmSystem.c \
../Core/Src/Button.c \
../Core/Src/Buzzer.c \
../Core/Src/GasSensor.c \
../Core/Src/LED_Driver.c \
../Core/Src/LED_Handler.c \
../Core/Src/LedRow.c \
../Core/Src/MQ9FlyingFish.c \
../Core/Src/SignalSystem.c \
../Core/Src/TopLayer.c \
../Core/Src/UART.c \
../Core/Src/UART_CommandSystem.c \
../Core/Src/main.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c 

C_DEPS += \
./Core/Src/AirQualityIndicator.d \
./Core/Src/AlarmSystem.d \
./Core/Src/Button.d \
./Core/Src/Buzzer.d \
./Core/Src/GasSensor.d \
./Core/Src/LED_Driver.d \
./Core/Src/LED_Handler.d \
./Core/Src/LedRow.d \
./Core/Src/MQ9FlyingFish.d \
./Core/Src/SignalSystem.d \
./Core/Src/TopLayer.d \
./Core/Src/UART.d \
./Core/Src/UART_CommandSystem.d \
./Core/Src/main.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d 

OBJS += \
./Core/Src/AirQualityIndicator.o \
./Core/Src/AlarmSystem.o \
./Core/Src/Button.o \
./Core/Src/Buzzer.o \
./Core/Src/GasSensor.o \
./Core/Src/LED_Driver.o \
./Core/Src/LED_Handler.o \
./Core/Src/LedRow.o \
./Core/Src/MQ9FlyingFish.o \
./Core/Src/SignalSystem.o \
./Core/Src/TopLayer.o \
./Core/Src/UART.o \
./Core/Src/UART_CommandSystem.o \
./Core/Src/main.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F750xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/AirQualityIndicator.cyclo ./Core/Src/AirQualityIndicator.d ./Core/Src/AirQualityIndicator.o ./Core/Src/AirQualityIndicator.su ./Core/Src/AlarmSystem.cyclo ./Core/Src/AlarmSystem.d ./Core/Src/AlarmSystem.o ./Core/Src/AlarmSystem.su ./Core/Src/Button.cyclo ./Core/Src/Button.d ./Core/Src/Button.o ./Core/Src/Button.su ./Core/Src/Buzzer.cyclo ./Core/Src/Buzzer.d ./Core/Src/Buzzer.o ./Core/Src/Buzzer.su ./Core/Src/GasSensor.cyclo ./Core/Src/GasSensor.d ./Core/Src/GasSensor.o ./Core/Src/GasSensor.su ./Core/Src/LED_Driver.cyclo ./Core/Src/LED_Driver.d ./Core/Src/LED_Driver.o ./Core/Src/LED_Driver.su ./Core/Src/LED_Handler.cyclo ./Core/Src/LED_Handler.d ./Core/Src/LED_Handler.o ./Core/Src/LED_Handler.su ./Core/Src/LedRow.cyclo ./Core/Src/LedRow.d ./Core/Src/LedRow.o ./Core/Src/LedRow.su ./Core/Src/MQ9FlyingFish.cyclo ./Core/Src/MQ9FlyingFish.d ./Core/Src/MQ9FlyingFish.o ./Core/Src/MQ9FlyingFish.su ./Core/Src/SignalSystem.cyclo ./Core/Src/SignalSystem.d ./Core/Src/SignalSystem.o ./Core/Src/SignalSystem.su ./Core/Src/TopLayer.cyclo ./Core/Src/TopLayer.d ./Core/Src/TopLayer.o ./Core/Src/TopLayer.su ./Core/Src/UART.cyclo ./Core/Src/UART.d ./Core/Src/UART.o ./Core/Src/UART.su ./Core/Src/UART_CommandSystem.cyclo ./Core/Src/UART_CommandSystem.d ./Core/Src/UART_CommandSystem.o ./Core/Src/UART_CommandSystem.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f7xx_hal_msp.cyclo ./Core/Src/stm32f7xx_hal_msp.d ./Core/Src/stm32f7xx_hal_msp.o ./Core/Src/stm32f7xx_hal_msp.su ./Core/Src/stm32f7xx_it.cyclo ./Core/Src/stm32f7xx_it.d ./Core/Src/stm32f7xx_it.o ./Core/Src/stm32f7xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f7xx.cyclo ./Core/Src/system_stm32f7xx.d ./Core/Src/system_stm32f7xx.o ./Core/Src/system_stm32f7xx.su

.PHONY: clean-Core-2f-Src

