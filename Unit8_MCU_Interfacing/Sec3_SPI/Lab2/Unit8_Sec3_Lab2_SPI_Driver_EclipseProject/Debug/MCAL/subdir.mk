################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/atmega32_gpio.c \
../MCAL/atmega32_spi.c 

OBJS += \
./MCAL/atmega32_gpio.o \
./MCAL/atmega32_spi.o 

C_DEPS += \
./MCAL/atmega32_gpio.d \
./MCAL/atmega32_spi.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c MCAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Studying\Embedded_KS\EclipseWorkSpace\Unit8_Sec3_Lab2_SPI_Driver_EclipseProject\inc" -I"D:\Studying\Embedded_KS\EclipseWorkSpace\Unit8_Sec3_Lab2_SPI_Driver_EclipseProject\MCAL\inc" -Wall -g2 -gdwarf-2 -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


