################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HCSR04_Files/HCSR04.c 

OBJS += \
./HCSR04_Files/HCSR04.o 

C_DEPS += \
./HCSR04_Files/HCSR04.d 


# Each subdirectory must supply rules for building sources it contributes
HCSR04_Files/%.o: ../HCSR04_Files/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8a -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


