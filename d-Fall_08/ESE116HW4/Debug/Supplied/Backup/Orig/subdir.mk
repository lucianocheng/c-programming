################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Supplied/Backup/Orig/debug.c \
../Supplied/Backup/Orig/demo.c \
../Supplied/Backup/Orig/pointers.c 

OBJS += \
./Supplied/Backup/Orig/debug.o \
./Supplied/Backup/Orig/demo.o \
./Supplied/Backup/Orig/pointers.o 

C_DEPS += \
./Supplied/Backup/Orig/debug.d \
./Supplied/Backup/Orig/demo.d \
./Supplied/Backup/Orig/pointers.d 


# Each subdirectory must supply rules for building sources it contributes
Supplied/Backup/Orig/%.o: ../Supplied/Backup/Orig/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


