################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include LCD_Files/subdir.mk
-include HCSR04_Files/subdir.mk
-include ADC_Files/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
SMIW_Project.lss \

FLASH_IMAGE += \
SMIW_Project.hex \

EEPROM_IMAGE += \
SMIW_Project.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: SMIW_Project.elf secondary-outputs

# Tool invocations
SMIW_Project.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,SMIW_Project.map -mmcu=atmega8a -o "SMIW_Project.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

SMIW_Project.lss: SMIW_Project.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S SMIW_Project.elf  >"SMIW_Project.lss"
	@echo 'Finished building: $@'
	@echo ' '

SMIW_Project.hex: SMIW_Project.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex SMIW_Project.elf  "SMIW_Project.hex"
	@echo 'Finished building: $@'
	@echo ' '

SMIW_Project.eep: SMIW_Project.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex SMIW_Project.elf  "SMIW_Project.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: SMIW_Project.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8a SMIW_Project.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) SMIW_Project.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
