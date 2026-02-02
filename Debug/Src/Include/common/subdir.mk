################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/Include/common/common.cpp 

OBJS += \
./Src/Include/common/common.o 

CPP_DEPS += \
./Src/Include/common/common.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Include/common/%.o Src/Include/common/%.su Src/Include/common/%.cyclo: ../Src/Include/common/%.cpp Src/Include/common/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"E:/ProjectDATN/Src/Application/Inc" -I"E:/ProjectDATN/Src/Application" -I"E:/ProjectDATN/Src/Include/common" -I"E:/ProjectDATN/Src/Driver/DriverAbstract" -I"E:/ProjectDATN/Src/Driver/DriverSTM32/Inc" -I"E:/ProjectDATN/Src/Driver/DriverSTM32" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Include-2f-common

clean-Src-2f-Include-2f-common:
	-$(RM) ./Src/Include/common/common.cyclo ./Src/Include/common/common.d ./Src/Include/common/common.o ./Src/Include/common/common.su

.PHONY: clean-Src-2f-Include-2f-common

