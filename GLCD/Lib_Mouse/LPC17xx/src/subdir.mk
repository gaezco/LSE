################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Descriptors.c \
../src/Mouse.c \
../src/cr_startup_lpc176x.c 

OBJS += \
./src/Descriptors.o \
./src/Mouse.o \
./src/cr_startup_lpc176x.o 

C_DEPS += \
./src/Descriptors.d \
./src/Mouse.d \
./src/cr_startup_lpc176x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__LPC17XX__ -DUSB_DEVICE_ONLY -D__CODE_RED -D__REDLIB__ -I"C:\Documents and Settings\Herny\Escritorio\GLCD\Lib_Mouse\inc" -I"C:\Documents and Settings\Herny\Escritorio\GLCD\LPCUSBlib\Drivers\USB" -I"C:\Documents and Settings\Herny\Escritorio\GLCD\Lib_Mouse" -I"C:\Documents and Settings\Herny\Escritorio\GLCD\Lib_TouchPanel\inc" -I"C:\Documents and Settings\Herny\Escritorio\GLCD\Lib_MCU\inc" -I"C:\Documents and Settings\Herny\Escritorio\GLCD\Lib_CMSISv1p30_LPC17xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -std=gnu99 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


