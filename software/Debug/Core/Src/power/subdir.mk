################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/power/boost_compensators.c \
../Core/Src/power/scr.c \
../Core/Src/power/zcd.c 

OBJS += \
./Core/Src/power/boost_compensators.o \
./Core/Src/power/scr.o \
./Core/Src/power/zcd.o 

C_DEPS += \
./Core/Src/power/boost_compensators.d \
./Core/Src/power/scr.d \
./Core/Src/power/zcd.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/power/%.o Core/Src/power/%.su Core/Src/power/%.cyclo: ../Core/Src/power/%.c Core/Src/power/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-power

clean-Core-2f-Src-2f-power:
	-$(RM) ./Core/Src/power/boost_compensators.cyclo ./Core/Src/power/boost_compensators.d ./Core/Src/power/boost_compensators.o ./Core/Src/power/boost_compensators.su ./Core/Src/power/scr.cyclo ./Core/Src/power/scr.d ./Core/Src/power/scr.o ./Core/Src/power/scr.su ./Core/Src/power/zcd.cyclo ./Core/Src/power/zcd.d ./Core/Src/power/zcd.o ./Core/Src/power/zcd.su

.PHONY: clean-Core-2f-Src-2f-power

