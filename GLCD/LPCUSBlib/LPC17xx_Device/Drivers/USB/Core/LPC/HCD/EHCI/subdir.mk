################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/USB/Core/LPC/HCD/EHCI/EHCI.c 

OBJS += \
./Drivers/USB/Core/LPC/HCD/EHCI/EHCI.o 

C_DEPS += \
./Drivers/USB/Core/LPC/HCD/EHCI/EHCI.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/USB/Core/LPC/HCD/EHCI/%.o: ../Drivers/USB/Core/LPC/HCD/EHCI/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__LPC17XX__ -DUSB_DEVICE_ONLY -D__CODE_RED -D__REDLIB__ -I"C:\Documents and Settings\Herny\Escritorio\GLCD\Lib_MCU\inc" -I"C:\Documents and Settings\Herny\Escritorio\GLCD\Lib_CMSISv1p30_LPC17xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -std=gnu99 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


