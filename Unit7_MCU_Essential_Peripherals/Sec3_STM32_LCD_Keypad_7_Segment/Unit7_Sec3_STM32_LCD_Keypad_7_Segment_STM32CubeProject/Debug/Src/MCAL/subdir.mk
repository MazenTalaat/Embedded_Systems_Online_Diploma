################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/MCAL/delay.c \
../Src/MCAL/stm32f103c6_gpio.c 

OBJS += \
./Src/MCAL/delay.o \
./Src/MCAL/stm32f103c6_gpio.o 

C_DEPS += \
./Src/MCAL/delay.d \
./Src/MCAL/stm32f103c6_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Src/MCAL/%.o Src/MCAL/%.su Src/MCAL/%.cyclo: ../Src/MCAL/%.c Src/MCAL/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_Sec3_STM32_LCD_Keypad_7_Segment_STM32CubeProject/Src" -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_Sec3_STM32_LCD_Keypad_7_Segment_STM32CubeProject/Inc/HAL" -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_Sec3_STM32_LCD_Keypad_7_Segment_STM32CubeProject/Inc/MCAL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-MCAL

clean-Src-2f-MCAL:
	-$(RM) ./Src/MCAL/delay.cyclo ./Src/MCAL/delay.d ./Src/MCAL/delay.o ./Src/MCAL/delay.su ./Src/MCAL/stm32f103c6_gpio.cyclo ./Src/MCAL/stm32f103c6_gpio.d ./Src/MCAL/stm32f103c6_gpio.o ./Src/MCAL/stm32f103c6_gpio.su

.PHONY: clean-Src-2f-MCAL

