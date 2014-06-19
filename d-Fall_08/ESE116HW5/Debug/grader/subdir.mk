################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../grader/hw05-tester.c \
../grader/testGetChar.c \
../grader/testGetWord.c \
../grader/testSortAndDeleteDuplicates.c \
../grader/tokenizer.c 

OBJS += \
./grader/hw05-tester.o \
./grader/testGetChar.o \
./grader/testGetWord.o \
./grader/testSortAndDeleteDuplicates.o \
./grader/tokenizer.o 

C_DEPS += \
./grader/hw05-tester.d \
./grader/testGetChar.d \
./grader/testGetWord.d \
./grader/testSortAndDeleteDuplicates.d \
./grader/tokenizer.d 


# Each subdirectory must supply rules for building sources it contributes
grader/%.o: ../grader/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


