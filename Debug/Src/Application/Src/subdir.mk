################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/Application/Src/BME280Task.cpp \
../Src/Application/Src/GPSTask.cpp \
../Src/Application/Src/IMUTask.cpp \
../Src/Application/Src/LoraComunicationTask.cpp \
../Src/Application/Src/MicroSDTask.cpp \
../Src/Application/Src/common.cpp 

OBJS += \
./Src/Application/Src/BME280Task.o \
./Src/Application/Src/GPSTask.o \
./Src/Application/Src/IMUTask.o \
./Src/Application/Src/LoraComunicationTask.o \
./Src/Application/Src/MicroSDTask.o \
./Src/Application/Src/common.o 

CPP_DEPS += \
./Src/Application/Src/BME280Task.d \
./Src/Application/Src/GPSTask.d \
./Src/Application/Src/IMUTask.d \
./Src/Application/Src/LoraComunicationTask.d \
./Src/Application/Src/MicroSDTask.d \
./Src/Application/Src/common.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Application/Src/%.o Src/Application/Src/%.su Src/Application/Src/%.cyclo: ../Src/Application/Src/%.cpp Src/Application/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"E:/ProjectDATN/Src/Include/common" -I"E:/ProjectDATN/Src/Driver/DriverAbstract" -I"E:/ProjectDATN/Src/Driver/DriverSTM32/Inc" -I"E:/ProjectDATN/Src/Driver/DriverSTM32" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-Application-2f-Src

clean-Src-2f-Application-2f-Src:
	-$(RM) ./Src/Application/Src/BME280Task.cyclo ./Src/Application/Src/BME280Task.d ./Src/Application/Src/BME280Task.o ./Src/Application/Src/BME280Task.su ./Src/Application/Src/GPSTask.cyclo ./Src/Application/Src/GPSTask.d ./Src/Application/Src/GPSTask.o ./Src/Application/Src/GPSTask.su ./Src/Application/Src/IMUTask.cyclo ./Src/Application/Src/IMUTask.d ./Src/Application/Src/IMUTask.o ./Src/Application/Src/IMUTask.su ./Src/Application/Src/LoraComunicationTask.cyclo ./Src/Application/Src/LoraComunicationTask.d ./Src/Application/Src/LoraComunicationTask.o ./Src/Application/Src/LoraComunicationTask.su ./Src/Application/Src/MicroSDTask.cyclo ./Src/Application/Src/MicroSDTask.d ./Src/Application/Src/MicroSDTask.o ./Src/Application/Src/MicroSDTask.su ./Src/Application/Src/common.cyclo ./Src/Application/Src/common.d ./Src/Application/Src/common.o ./Src/Application/Src/common.su

.PHONY: clean-Src-2f-Application-2f-Src

