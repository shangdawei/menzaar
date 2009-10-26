################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../connection_handler.c \
../main.c \
../misc_functions.c \
../ocm.c \
../sla_db.c \
../tcp_client.c 

OBJS += \
./connection_handler.o \
./main.o \
./misc_functions.o \
./ocm.o \
./sla_db.o \
./tcp_client.o 

C_DEPS += \
./connection_handler.d \
./main.d \
./misc_functions.d \
./ocm.d \
./sla_db.d \
./tcp_client.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


