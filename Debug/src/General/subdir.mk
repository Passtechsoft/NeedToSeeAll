################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/General/general.cpp \
../src/General/utilities.cpp 

OBJS += \
./src/General/general.o \
./src/General/utilities.o 

CPP_DEPS += \
./src/General/general.d \
./src/General/utilities.d 


# Each subdirectory must supply rules for building sources it contributes
src/General/%.o: ../src/General/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


