################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App.c \
../UART_Lcfg.c \
../gpio.c \
../keypad.c \
../lcd.c \
../timer1.c \
../timer1_Lcfg.c \
../uart.c 

OBJS += \
./App.o \
./UART_Lcfg.o \
./gpio.o \
./keypad.o \
./lcd.o \
./timer1.o \
./timer1_Lcfg.o \
./uart.o 

C_DEPS += \
./App.d \
./UART_Lcfg.d \
./gpio.d \
./keypad.d \
./lcd.d \
./timer1.d \
./timer1_Lcfg.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


