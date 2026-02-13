################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Board/STM32F407VGT6/debug/debug.cpp 

OBJS += \
./Board/STM32F407VGT6/debug/debug.o 

CPP_DEPS += \
./Board/STM32F407VGT6/debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Board/STM32F407VGT6/debug/%.o Board/STM32F407VGT6/debug/%.su Board/STM32F407VGT6/debug/%.cyclo: ../Board/STM32F407VGT6/debug/%.cpp Board/STM32F407VGT6/debug/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"E:/ProjectDATN/Board/STM32F407VGT6/debug" -I"E:/ProjectDATN/Board/STM32F407VGT6/initTask" -I"E:/ProjectDATN/Src/Module/Device_driver/Magnetometer" -I"E:/ProjectDATN/Src/Module/Device_driver/MPU" -I"E:/ProjectDATN/Src/Application/Inc" -I"E:/ProjectDATN/Src/Application" -I"E:/ProjectDATN/Src/Include/common" -I"E:/ProjectDATN/Src/Driver/DriverAbstract" -I"E:/ProjectDATN/Src/Driver/DriverSTM32/Inc" -I"E:/ProjectDATN/Src/Driver/DriverSTM32" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Board-2f-STM32F407VGT6-2f-debug

clean-Board-2f-STM32F407VGT6-2f-debug:
	-$(RM) ./Board/STM32F407VGT6/debug/debug.cyclo ./Board/STM32F407VGT6/debug/debug.d ./Board/STM32F407VGT6/debug/debug.o ./Board/STM32F407VGT6/debug/debug.su

.PHONY: clean-Board-2f-STM32F407VGT6-2f-debug

