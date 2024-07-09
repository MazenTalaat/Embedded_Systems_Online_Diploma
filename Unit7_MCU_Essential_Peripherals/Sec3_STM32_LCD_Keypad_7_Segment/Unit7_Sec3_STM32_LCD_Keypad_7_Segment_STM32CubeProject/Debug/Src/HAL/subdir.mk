################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/HAL/keypad.c \
../Src/HAL/lcd.c \
../Src/HAL/seven_segment.c 

OBJS += \
./Src/HAL/keypad.o \
./Src/HAL/lcd.o \
./Src/HAL/seven_segment.o 

C_DEPS += \
./Src/HAL/keypad.d \
./Src/HAL/lcd.d \
./Src/HAL/seven_segment.d 


# Each subdirectory must supply rules for building sources it contributes
Src/HAL/%.o Src/HAL/%.su Src/HAL/%.cyclo: ../Src/HAL/%.c Src/HAL/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_Sec3_STM32_LCD_Keypad_7_Segment_STM32CubeProject/Src" -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_Sec3_STM32_LCD_Keypad_7_Segment_STM32CubeProject/Inc/HAL" -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit7_Sec3_STM32_LCD_Keypad_7_Segment_STM32CubeProject/Inc/MCAL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src-2f-HAL

clean-Src-2f-HAL:
	-$(RM) ./Src/HAL/keypad.cyclo ./Src/HAL/keypad.d ./Src/HAL/keypad.o ./Src/HAL/keypad.su ./Src/HAL/lcd.cyclo ./Src/HAL/lcd.d ./Src/HAL/lcd.o ./Src/HAL/lcd.su ./Src/HAL/seven_segment.cyclo ./Src/HAL/seven_segment.d ./Src/HAL/seven_segment.o ./Src/HAL/seven_segment.su

.PHONY: clean-Src-2f-HAL

