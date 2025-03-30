################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../DCMotor.c \
../external_eeprom.c \
../gpio.c \
../i2c.c \
../mcu2.c \
../pir.c \
../pwm.c \
../timer0.c \
../uart.c 

OBJS += \
./Buzzer.o \
./DCMotor.o \
./external_eeprom.o \
./gpio.o \
./i2c.o \
./mcu2.o \
./pir.o \
./pwm.o \
./timer0.o \
./uart.o 

C_DEPS += \
./Buzzer.d \
./DCMotor.d \
./external_eeprom.d \
./gpio.d \
./i2c.d \
./mcu2.d \
./pir.d \
./pwm.d \
./timer0.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


