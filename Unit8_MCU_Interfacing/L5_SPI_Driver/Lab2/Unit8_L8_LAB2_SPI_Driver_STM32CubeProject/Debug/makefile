################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include MCAL/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Unit8_L8_LAB2_SPI_Driver_STM32CubeProject
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.elf \

MAP_FILES += \
Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.list \


# All Target
all: main-build

# Main-build Target
main-build: Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.elf secondary-outputs

# Tool invocations
Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.elf Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.map: $(OBJS) $(USER_OBJS) D:\Studying\Embedded_KS\STM32CubeWorkSpace\Unit8_L8_LAB2_SPI_Driver_STM32CubeProject\STM32F103C6TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -gdwarf-2 -o "Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\Studying\Embedded_KS\STM32CubeWorkSpace\Unit8_L8_LAB2_SPI_Driver_STM32CubeProject\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.elf Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.list Unit8_L8_LAB2_SPI_Driver_STM32CubeProject.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
