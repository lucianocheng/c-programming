################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Supplied/Scratch/debug.c \
../Supplied/Scratch/demo.c \
../Supplied/Scratch/p.c \
../Supplied/Scratch/pointers.c \
../Supplied/Scratch/stuff.c 

OBJS += \
./Supplied/Scratch/debug.o \
./Supplied/Scratch/demo.o \
./Supplied/Scratch/p.o \
./Supplied/Scratch/pointers.o \
./Supplied/Scratch/stuff.o 

C_DEPS += \
./Supplied/Scratch/debug.d \
./Supplied/Scratch/demo.d \
./Supplied/Scratch/p.d \
./Supplied/Scratch/pointers.d \
./Supplied/Scratch/stuff.d 


# Each subdirectory must supply rules for building sources it contributes
Supplied/Scratch/%.o: ../Supplied/Scratch/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


