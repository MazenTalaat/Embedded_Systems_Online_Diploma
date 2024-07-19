################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/stm32f103c6_gpio.c \
../MCAL/stm32f103c6_rcc.c \
../MCAL/stm32f103c6_spi.c \
../MCAL/stm32f103c6_usart.c 

OBJS += \
./MCAL/stm32f103c6_gpio.o \
./MCAL/stm32f103c6_rcc.o \
./MCAL/stm32f103c6_spi.o \
./MCAL/stm32f103c6_usart.o 

C_DEPS += \
./MCAL/stm32f103c6_gpio.d \
./MCAL/stm32f103c6_rcc.d \
./MCAL/stm32f103c6_spi.d \
./MCAL/stm32f103c6_usart.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o MCAL/%.su MCAL/%.cyclo: ../MCAL/%.c MCAL/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/Studying/Embedded_KS/STM32CubeWorkSpace/Unit8_L5_LAB2_SPI_Driver_STM32CubeProject/MCAL/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL

clean-MCAL:
	-$(RM) ./MCAL/stm32f103c6_gpio.cyclo ./MCAL/stm32f103c6_gpio.d ./MCAL/stm32f103c6_gpio.o ./MCAL/stm32f103c6_gpio.su ./MCAL/stm32f103c6_rcc.cyclo ./MCAL/stm32f103c6_rcc.d ./MCAL/stm32f103c6_rcc.o ./MCAL/stm32f103c6_rcc.su ./MCAL/stm32f103c6_spi.cyclo ./MCAL/stm32f103c6_spi.d ./MCAL/stm32f103c6_spi.o ./MCAL/stm32f103c6_spi.su ./MCAL/stm32f103c6_usart.cyclo ./MCAL/stm32f103c6_usart.d ./MCAL/stm32f103c6_usart.o ./MCAL/stm32f103c6_usart.su

.PHONY: clean-MCAL

