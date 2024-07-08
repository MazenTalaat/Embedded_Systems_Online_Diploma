################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F103C6_Drivers/stm32f103c6_gpio.c 

OBJS += \
./STM32F103C6_Drivers/stm32f103c6_gpio.o 

C_DEPS += \
./STM32F103C6_Drivers/stm32f103c6_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F103C6_Drivers/%.o STM32F103C6_Drivers/%.su STM32F103C6_Drivers/%.cyclo: ../STM32F103C6_Drivers/%.c STM32F103C6_Drivers/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_L3_GPIO_Driver_STM32CubeProject/STM32F103C6_Drivers" -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_L3_GPIO_Driver_STM32CubeProject/STM32F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-STM32F103C6_Drivers

clean-STM32F103C6_Drivers:
	-$(RM) ./STM32F103C6_Drivers/stm32f103c6_gpio.cyclo ./STM32F103C6_Drivers/stm32f103c6_gpio.d ./STM32F103C6_Drivers/stm32f103c6_gpio.o ./STM32F103C6_Drivers/stm32f103c6_gpio.su

.PHONY: clean-STM32F103C6_Drivers

