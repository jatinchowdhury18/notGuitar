################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RingMod_Main.c \
../c6713dskinit.c 

ASM_SRCS += \
../Vectors_intr.asm 

CMD_SRCS += \
../C6713dsk.cmd 

ASM_DEPS += \
./Vectors_intr.pp 

OBJS += \
./RingMod_Main.obj \
./Vectors_intr.obj \
./c6713dskinit.obj 

C_DEPS += \
./RingMod_Main.pp \
./c6713dskinit.pp 

OBJS__QTD += \
".\RingMod_Main.obj" \
".\Vectors_intr.obj" \
".\c6713dskinit.obj" 

ASM_DEPS__QTD += \
".\Vectors_intr.pp" 

C_DEPS__QTD += \
".\RingMod_Main.pp" \
".\c6713dskinit.pp" 

C_SRCS_QUOTED += \
"../RingMod_Main.c" \
"../c6713dskinit.c" 

ASM_SRCS_QUOTED += \
"../Vectors_intr.asm" 


# Each subdirectory must supply rules for building sources it contributes
RingMod_Main.obj: ../RingMod_Main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.0.4/bin/cl6x" -mv6700 -g --define=CHIP_6713 --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.0.4/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/dsk6713/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/dsk6713/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/csl/include" --diag_warning=225 --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="RingMod_Main.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

Vectors_intr.obj: ../Vectors_intr.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.0.4/bin/cl6x" -mv6700 -g --define=CHIP_6713 --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.0.4/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/dsk6713/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/dsk6713/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/csl/include" --diag_warning=225 --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="Vectors_intr.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

c6713dskinit.obj: ../c6713dskinit.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.0.4/bin/cl6x" -mv6700 -g --define=CHIP_6713 --include_path="C:/Program Files (x86)/Texas Instruments/C6000 Code Generation Tools 7.0.4/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/dsk6713/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/dsk6713/include" --include_path="C:/Program Files (x86)/Texas Instruments/ccsv4/C6000/csl/include" --diag_warning=225 --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="c6713dskinit.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


