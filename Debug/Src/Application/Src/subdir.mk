################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/Application/Src/EKFTask.cpp \
../Src/Application/Src/GCSTask.cpp \
../Src/Application/Src/PIDTask.cpp \
../Src/Application/Src/common.cpp \
../Src/Application/Src/flightControlTask.cpp \
../Src/Application/Src/memoryTask.cpp \
../Src/Application/Src/readGPSTask.cpp \
../Src/Application/Src/readIMUTask.cpp \
../Src/Application/Src/readMagTask.cpp \
../Src/Application/Src/readPressTask.cpp 

OBJS += \
./Src/Application/Src/EKFTask.o \
./Src/Application/Src/GCSTask.o \
./Src/Application/Src/PIDTask.o \
./Src/Application/Src/common.o \
./Src/Application/Src/flightControlTask.o \
./Src/Application/Src/memoryTask.o \
./Src/Application/Src/readGPSTask.o \
./Src/Application/Src/readIMUTask.o \
./Src/Application/Src/readMagTask.o \
./Src/Application/Src/readPressTask.o 

CPP_DEPS += \
./Src/Application/Src/EKFTask.d \
./Src/Application/Src/GCSTask.d \
./Src/Application/Src/PIDTask.d \
./Src/Application/Src/common.d \
./Src/Application/Src/flightControlTask.d \
./Src/Application/Src/memoryTask.d \
./Src/Application/Src/readGPSTask.d \
./Src/Application/Src/readIMUTask.d \
./Src/Application/Src/readMagTask.d \
./Src/Application/Src/readPressTask.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Application/Src/%.o Src/Application/Src/%.su Src/Application/Src/%.cyclo: ../Src/Application/Src/%.cpp Src/Application/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"E:/ProjectDATN/Src/Module/Device_driver/MPU" -I"E:/ProjectDATN/Src/Application/Inc" -I"E:/ProjectDATN/Src/Application" -I"E:/ProjectDATN/Src/Include/common" -I"E:/ProjectDATN/Src/Driver/DriverAbstract" -I"E:/ProjectDATN/Src/Driver/DriverSTM32/Inc" -I"E:/ProjectDATN/Src/Driver/DriverSTM32" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Application-2f-Src

clean-Src-2f-Application-2f-Src:
	-$(RM) ./Src/Application/Src/EKFTask.cyclo ./Src/Application/Src/EKFTask.d ./Src/Application/Src/EKFTask.o ./Src/Application/Src/EKFTask.su ./Src/Application/Src/GCSTask.cyclo ./Src/Application/Src/GCSTask.d ./Src/Application/Src/GCSTask.o ./Src/Application/Src/GCSTask.su ./Src/Application/Src/PIDTask.cyclo ./Src/Application/Src/PIDTask.d ./Src/Application/Src/PIDTask.o ./Src/Application/Src/PIDTask.su ./Src/Application/Src/common.cyclo ./Src/Application/Src/common.d ./Src/Application/Src/common.o ./Src/Application/Src/common.su ./Src/Application/Src/flightControlTask.cyclo ./Src/Application/Src/flightControlTask.d ./Src/Application/Src/flightControlTask.o ./Src/Application/Src/flightControlTask.su ./Src/Application/Src/memoryTask.cyclo ./Src/Application/Src/memoryTask.d ./Src/Application/Src/memoryTask.o ./Src/Application/Src/memoryTask.su ./Src/Application/Src/readGPSTask.cyclo ./Src/Application/Src/readGPSTask.d ./Src/Application/Src/readGPSTask.o ./Src/Application/Src/readGPSTask.su ./Src/Application/Src/readIMUTask.cyclo ./Src/Application/Src/readIMUTask.d ./Src/Application/Src/readIMUTask.o ./Src/Application/Src/readIMUTask.su ./Src/Application/Src/readMagTask.cyclo ./Src/Application/Src/readMagTask.d ./Src/Application/Src/readMagTask.o ./Src/Application/Src/readMagTask.su ./Src/Application/Src/readPressTask.cyclo ./Src/Application/Src/readPressTask.d ./Src/Application/Src/readPressTask.o ./Src/Application/Src/readPressTask.su

.PHONY: clean-Src-2f-Application-2f-Src

