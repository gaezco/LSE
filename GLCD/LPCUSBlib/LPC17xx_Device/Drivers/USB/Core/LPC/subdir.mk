################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/USB/Core/LPC/Device_LPC.c \
../Drivers/USB/Core/LPC/EndpointStream_LPC.c \
../Drivers/USB/Core/LPC/Endpoint_LPC.c \
../Drivers/USB/Core/LPC/Host_LPC.c \
../Drivers/USB/Core/LPC/PipeStream_LPC.c \
../Drivers/USB/Core/LPC/Pipe_LPC.c \
../Drivers/USB/Core/LPC/USBController_LPC.c 

OBJS += \
./Drivers/USB/Core/LPC/Device_LPC.o \
./Drivers/USB/Core/LPC/EndpointStream_LPC.o \
./Drivers/USB/Core/LPC/Endpoint_LPC.o \
./Drivers/USB/Core/LPC/Host_LPC.o \
./Drivers/USB/Core/LPC/PipeStream_LPC.o \
./Drivers/USB/Core/LPC/Pipe_LPC.o \
./Drivers/USB/Core/LPC/USBController_LPC.o 

C_DEPS += \
./Drivers/USB/Core/LPC/Device_LPC.d \
./Drivers/USB/Core/LPC/EndpointStream_LPC.d \
./Drivers/USB/Core/LPC/Endpoint_LPC.d \
./Drivers/USB/Core/LPC/Host_LPC.d \
./Drivers/USB/Core/LPC/PipeStream_LPC.d \
./Drivers/USB/Core/LPC/Pipe_LPC.d \
./Drivers/USB/Core/LPC/USBController_LPC.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/USB/Core/LPC/%.o: ../Drivers/USB/Core/LPC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__LPC17XX__ -DUSB_DEVICE_ONLY -D__CODE_RED -D__REDLIB__ -I"C:\Documents and Settings\Herny\Escritorio\GLCD\Lib_MCU\inc" -I"C:\Documents and Settings\Herny\Escritorio\GLCD\Lib_CMSISv1p30_LPC17xx\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -std=gnu99 -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


