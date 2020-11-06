################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
C:/Users/karn001/Desktop/Exercises/Part\ 2\ of\ 2_By\ Prof\ Seow\ CK/EE4413_C515/C5515_Support_Files/C5515_Lib/dsplib_2.40.00/55xdspx_LARGE.lib 

C_SRCS += \
../AIC_func.c \
../hadamard.c \
../main.c \
../sar.c 

CMD_SRCS += \
../lnkx.cmd 

OBJS += \
./AIC_func.obj \
./hadamard.obj \
./main.obj \
./sar.obj 

C_DEPS += \
./AIC_func.pp \
./hadamard.pp \
./main.pp \
./sar.pp 

OBJS__QTD += \
".\AIC_func.obj" \
".\hadamard.obj" \
".\main.obj" \
".\sar.obj" 

C_DEPS__QTD += \
".\AIC_func.pp" \
".\hadamard.pp" \
".\main.pp" \
".\sar.pp" 

C_SRCS_QUOTED += \
"../AIC_func.c" \
"../hadamard.c" \
"../main.c" \
"../sar.c" 


# Each subdirectory must supply rules for building sources it contributes
AIC_func.obj: ../AIC_func.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/Ex4" --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Lib/dsplib_2.40.00/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="AIC_func.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

hadamard.obj: ../hadamard.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/Ex4" --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Lib/dsplib_2.40.00/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="hadamard.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/Ex4" --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Lib/dsplib_2.40.00/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

sar.obj: ../sar.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/Ex4" --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Lib/dsplib_2.40.00/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Includes" --diag_warning=225 --ptrdiff_size=32 --memory_model=large --preproc_with_compile --preproc_dependency="sar.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


