################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/OldClient.cpp \
../src/OldServer.cpp \
../src/Server.cpp \
../src/test.cpp 

OBJS += \
./src/OldClient.o \
./src/OldServer.o \
./src/Server.o \
./src/test.o 

CPP_DEPS += \
./src/OldClient.d \
./src/OldServer.d \
./src/Server.d \
./src/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


