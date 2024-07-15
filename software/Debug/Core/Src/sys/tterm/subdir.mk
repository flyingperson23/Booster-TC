################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/sys/tterm/TTerm.c \
../Core/Src/sys/tterm/TTerm_AC.c \
../Core/Src/sys/tterm/TTerm_cmd.c 

OBJS += \
./Core/Src/sys/tterm/TTerm.o \
./Core/Src/sys/tterm/TTerm_AC.o \
./Core/Src/sys/tterm/TTerm_cmd.o 

C_DEPS += \
./Core/Src/sys/tterm/TTerm.d \
./Core/Src/sys/tterm/TTerm_AC.d \
./Core/Src/sys/tterm/TTerm_cmd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/sys/tterm/%.o Core/Src/sys/tterm/%.su Core/Src/sys/tterm/%.cyclo: ../Core/Src/sys/tterm/%.c Core/Src/sys/tterm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-sys-2f-tterm

clean-Core-2f-Src-2f-sys-2f-tterm:
	-$(RM) ./Core/Src/sys/tterm/TTerm.cyclo ./Core/Src/sys/tterm/TTerm.d ./Core/Src/sys/tterm/TTerm.o ./Core/Src/sys/tterm/TTerm.su ./Core/Src/sys/tterm/TTerm_AC.cyclo ./Core/Src/sys/tterm/TTerm_AC.d ./Core/Src/sys/tterm/TTerm_AC.o ./Core/Src/sys/tterm/TTerm_AC.su ./Core/Src/sys/tterm/TTerm_cmd.cyclo ./Core/Src/sys/tterm/TTerm_cmd.d ./Core/Src/sys/tterm/TTerm_cmd.o ./Core/Src/sys/tterm/TTerm_cmd.su

.PHONY: clean-Core-2f-Src-2f-sys-2f-tterm

