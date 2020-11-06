################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./sar.obj" \
"./main.obj" \
"./hadamard.obj" \
"./AIC_func.obj" \
-l"rts55x.lib" \
-l"C:\Users\karn001\Desktop\Exercises\Part 2 of 2_By Prof Seow CK\EE4413_C515\C5515_Support_Files\usbstk5515bsl.lib" \
"C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Lib/dsplib_2.40.00/55xdspx_LARGE.lib" \
"../lnkx.cmd" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Ex3.out

# Tool invocations
Ex3.out: $(GEN_CMDS) $(CMD_SRCS) $(LIB_SRCS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -v5515 -g --diag_warning=225 --ptrdiff_size=32 --memory_model=large -z -m"Ex3.map" --warn_sections -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/lib" -i"C:/Users/karn001/Desktop/Exercises/Part 2 of 2_By Prof Seow CK/EE4413_C515/C5515_Support_Files/C5515_Lib" -i"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/include" --reread_libs --rom_model -o "Ex3.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C5500_EXECUTABLE_OUTPUTS__QTD) "Ex3.out"
	-$(RM) ".\AIC_func.obj" ".\hadamard.obj" ".\main.obj" ".\sar.obj" 
	-$(RM) ".\AIC_func.pp" ".\hadamard.pp" ".\main.pp" ".\sar.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
