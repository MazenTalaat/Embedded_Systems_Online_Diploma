################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/eeprom_i2c.c 

OBJS += \
./HAL/eeprom_i2c.o 

C_DEPS += \
./HAL/eeprom_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o HAL/%.su HAL/%.cyclo: ../HAL/%.c HAL/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit8_L7_I2C_Driver_STM32CubeProject/MCAL/Inc" -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit8_L7_I2C_Driver_STM32CubeProject/HAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL

clean-HAL:
	-$(RM) ./HAL/eeprom_i2c.cyclo ./HAL/eeprom_i2c.d ./HAL/eeprom_i2c.o ./HAL/eeprom_i2c.su

.PHONY: clean-HAL

