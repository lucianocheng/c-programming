################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Supplied/demo.c \
../Supplied/pointers.c \
../Supplied/pointers_lab.c \
../Supplied/pointers_main.c 

OBJS += \
./Supplied/demo.o \
./Supplied/pointers.o \
./Supplied/pointers_lab.o \
./Supplied/pointers_main.o 

C_DEPS += \
./Supplied/demo.d \
./Supplied/pointers.d \
./Supplied/pointers_lab.d \
./Supplied/pointers_main.d 


# Each subdirectory must supply rules for building sources it contributes
Supplied/%.o: ../Supplied/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


