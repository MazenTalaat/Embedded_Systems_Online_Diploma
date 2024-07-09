################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/delay.c \
../MCAL/stm32f103c6_exti.c \
../MCAL/stm32f103c6_gpio.c 

OBJS += \
./MCAL/delay.o \
./MCAL/stm32f103c6_exti.o \
./MCAL/stm32f103c6_gpio.o 

C_DEPS += \
./MCAL/delay.d \
./MCAL/stm32f103c6_exti.d \
./MCAL/stm32f103c6_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o MCAL/%.su MCAL/%.cyclo: ../MCAL/%.c MCAL/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_L4_EXTI_Driver_STM32CubeProject/HAL/Inc" -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_L4_EXTI_Driver_STM32CubeProject/MCAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL

clean-MCAL:
	-$(RM) ./MCAL/delay.cyclo ./MCAL/delay.d ./MCAL/delay.o ./MCAL/delay.su ./MCAL/stm32f103c6_exti.cyclo ./MCAL/stm32f103c6_exti.d ./MCAL/stm32f103c6_exti.o ./MCAL/stm32f103c6_exti.su ./MCAL/stm32f103c6_gpio.cyclo ./MCAL/stm32f103c6_gpio.d ./MCAL/stm32f103c6_gpio.o ./MCAL/stm32f103c6_gpio.su

.PHONY: clean-MCAL

