################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Supplied/Backup/debug.c \
../Supplied/Backup/newDebug.c \
../Supplied/Backup/pointers-pre2007Spring.c \
../Supplied/Backup/pointers.c \
../Supplied/Backup/pointers2.c 

OBJS += \
./Supplied/Backup/debug.o \
./Supplied/Backup/newDebug.o \
./Supplied/Backup/pointers-pre2007Spring.o \
./Supplied/Backup/pointers.o \
./Supplied/Backup/pointers2.o 

C_DEPS += \
./Supplied/Backup/debug.d \
./Supplied/Backup/newDebug.d \
./Supplied/Backup/pointers-pre2007Spring.d \
./Supplied/Backup/pointers.d \
./Supplied/Backup/pointers2.d 


# Each subdirectory must supply rules for building sources it contributes
Supplied/Backup/%.o: ../Supplied/Backup/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


