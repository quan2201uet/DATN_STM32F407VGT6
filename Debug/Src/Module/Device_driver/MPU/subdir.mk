################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/Module/Device_driver/MPU/mpu6050.cpp 

OBJS += \
./Src/Module/Device_driver/MPU/mpu6050.o 

CPP_DEPS += \
./Src/Module/Device_driver/MPU/mpu6050.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Module/Device_driver/MPU/%.o Src/Module/Device_driver/MPU/%.su Src/Module/Device_driver/MPU/%.cyclo: ../Src/Module/Device_driver/MPU/%.cpp Src/Module/Device_driver/MPU/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"E:/ProjectDATN/Src/Include/common" -I"E:/ProjectDATN/Src/Driver/DriverAbstract" -I"E:/ProjectDATN/Src/Driver/DriverSTM32/Inc" -I"E:/ProjectDATN/Src/Driver/DriverSTM32" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Module-2f-Device_driver-2f-MPU

clean-Src-2f-Module-2f-Device_driver-2f-MPU:
	-$(RM) ./Src/Module/Device_driver/MPU/mpu6050.cyclo ./Src/Module/Device_driver/MPU/mpu6050.d ./Src/Module/Device_driver/MPU/mpu6050.o ./Src/Module/Device_driver/MPU/mpu6050.su

.PHONY: clean-Src-2f-Module-2f-Device_driver-2f-MPU

