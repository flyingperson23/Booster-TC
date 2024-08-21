################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/status/fault.c \
../Core/Src/status/led.c 

OBJS += \
./Core/Src/status/fault.o \
./Core/Src/status/led.o 

C_DEPS += \
./Core/Src/status/fault.d \
./Core/Src/status/led.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/status/%.o Core/Src/status/%.su Core/Src/status/%.cyclo: ../Core/Src/status/%.c Core/Src/status/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-status

clean-Core-2f-Src-2f-status:
	-$(RM) ./Core/Src/status/fault.cyclo ./Core/Src/status/fault.d ./Core/Src/status/fault.o ./Core/Src/status/fault.su ./Core/Src/status/led.cyclo ./Core/Src/status/led.d ./Core/Src/status/led.o ./Core/Src/status/led.su

.PHONY: clean-Core-2f-Src-2f-status

