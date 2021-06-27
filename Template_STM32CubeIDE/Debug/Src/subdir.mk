################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32l4xx.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32l4xx.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/main.o: ../Src/main.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DSTM32L412KBUx -DSTM32L4 -DSTM32 -c -I../Inc -I"D:/CURSOS/STM32/MCU2/CODIGO/STM32F407VGT6/Template_STM32CubeIDE/DRIVERS/CMSIS/CORE" -I"D:/CURSOS/STM32/MCU2/CODIGO/STM32F407VGT6/Template_STM32CubeIDE/DRIVERS/CMSIS/Device/ST" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DSTM32L412KBUx -DSTM32L4 -DSTM32 -c -I../Inc -I"D:/CURSOS/STM32/MCU2/CODIGO/STM32F407VGT6/Template_STM32CubeIDE/DRIVERS/CMSIS/CORE" -I"D:/CURSOS/STM32/MCU2/CODIGO/STM32F407VGT6/Template_STM32CubeIDE/DRIVERS/CMSIS/Device/ST" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DSTM32L412KBUx -DSTM32L4 -DSTM32 -c -I../Inc -I"D:/CURSOS/STM32/MCU2/CODIGO/STM32F407VGT6/Template_STM32CubeIDE/DRIVERS/CMSIS/CORE" -I"D:/CURSOS/STM32/MCU2/CODIGO/STM32F407VGT6/Template_STM32CubeIDE/DRIVERS/CMSIS/Device/ST" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/system_stm32l4xx.o: ../Src/system_stm32l4xx.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L412xx -DSTM32L412KBUx -DSTM32L4 -DSTM32 -c -I../Inc -I"D:/CURSOS/STM32/MCU2/CODIGO/STM32F407VGT6/Template_STM32CubeIDE/DRIVERS/CMSIS/CORE" -I"D:/CURSOS/STM32/MCU2/CODIGO/STM32F407VGT6/Template_STM32CubeIDE/DRIVERS/CMSIS/Device/ST" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/system_stm32l4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

