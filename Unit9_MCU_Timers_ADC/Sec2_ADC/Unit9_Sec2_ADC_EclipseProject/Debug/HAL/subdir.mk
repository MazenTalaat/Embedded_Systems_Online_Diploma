################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/lcd.c \
../HAL/lm35_sensor.c 

OBJS += \
./HAL/lcd.o \
./HAL/lm35_sensor.o 

C_DEPS += \
./HAL/lcd.d \
./HAL/lm35_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Studying\Embedded_KS\EclipseWorkSpace\Unit9_Sec2_ADC_EclipseProject" -I"D:\Studying\Embedded_KS\EclipseWorkSpace\Unit9_Sec2_ADC_EclipseProject\HAL\Inc" -I"D:\Studying\Embedded_KS\EclipseWorkSpace\Unit9_Sec2_ADC_EclipseProject\Inc" -I"D:\Studying\Embedded_KS\EclipseWorkSpace\Unit9_Sec2_ADC_EclipseProject\MCAL\Inc" -Wall -g2 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


