################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sltn/weatherFunctions.c \
../Sltn/weatherTest.c 

OBJS += \
./Sltn/weatherFunctions.o \
./Sltn/weatherTest.o 

C_DEPS += \
./Sltn/weatherFunctions.d \
./Sltn/weatherTest.d 


# Each subdirectory must supply rules for building sources it contributes
Sltn/%.o: ../Sltn/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


