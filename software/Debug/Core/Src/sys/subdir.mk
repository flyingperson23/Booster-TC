################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/sys/cmds.c \
../Core/Src/sys/uart.c \
../Core/Src/sys/util.c \
../Core/Src/sys/vars.c 

OBJS += \
./Core/Src/sys/cmds.o \
./Core/Src/sys/uart.o \
./Core/Src/sys/util.o \
./Core/Src/sys/vars.o 

C_DEPS += \
./Core/Src/sys/cmds.d \
./Core/Src/sys/uart.d \
./Core/Src/sys/util.d \
./Core/Src/sys/vars.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sys/%.o Core/Src/sys/%.su Core/Src/sys/%.cyclo: ../Core/Src/sys/%.c Core/Src/sys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-sys

clean-Core-2f-Src-2f-sys:
	-$(RM) ./Core/Src/sys/cmds.cyclo ./Core/Src/sys/cmds.d ./Core/Src/sys/cmds.o ./Core/Src/sys/cmds.su ./Core/Src/sys/uart.cyclo ./Core/Src/sys/uart.d ./Core/Src/sys/uart.o ./Core/Src/sys/uart.su ./Core/Src/sys/util.cyclo ./Core/Src/sys/util.d ./Core/Src/sys/util.o ./Core/Src/sys/util.su ./Core/Src/sys/vars.cyclo ./Core/Src/sys/vars.d ./Core/Src/sys/vars.o ./Core/Src/sys/vars.su

.PHONY: clean-Core-2f-Src-2f-sys

