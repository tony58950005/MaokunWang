################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MyLibrary/PushButtonLedToggle.cpp 

OBJS += \
./MyLibrary/PushButtonLedToggle.o 

CPP_DEPS += \
./MyLibrary/PushButtonLedToggle.d 


# Each subdirectory must supply rules for building sources it contributes
MyLibrary/PushButtonLedToggle.o: ../MyLibrary/PushButtonLedToggle.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F446xx -DDEBUG -c -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I"C:/Users/59488/Desktop/push_Button_test/MyLibrary" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"MyLibrary/PushButtonLedToggle.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

