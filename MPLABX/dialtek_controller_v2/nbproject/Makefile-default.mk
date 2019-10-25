#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dialtek_controller_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dialtek_controller_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main_heater.c main_steppers.c main_dosing_sys.c main_io.c d_delay.c d_eeprom.c d_heater.c d_one_wire.c d_SPI.c dialtek_modbus.c dialtek_uart.c hamilton_pump.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main_heater.o ${OBJECTDIR}/main_steppers.o ${OBJECTDIR}/main_dosing_sys.o ${OBJECTDIR}/main_io.o ${OBJECTDIR}/d_delay.o ${OBJECTDIR}/d_eeprom.o ${OBJECTDIR}/d_heater.o ${OBJECTDIR}/d_one_wire.o ${OBJECTDIR}/d_SPI.o ${OBJECTDIR}/dialtek_modbus.o ${OBJECTDIR}/dialtek_uart.o ${OBJECTDIR}/hamilton_pump.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main_heater.o.d ${OBJECTDIR}/main_steppers.o.d ${OBJECTDIR}/main_dosing_sys.o.d ${OBJECTDIR}/main_io.o.d ${OBJECTDIR}/d_delay.o.d ${OBJECTDIR}/d_eeprom.o.d ${OBJECTDIR}/d_heater.o.d ${OBJECTDIR}/d_one_wire.o.d ${OBJECTDIR}/d_SPI.o.d ${OBJECTDIR}/dialtek_modbus.o.d ${OBJECTDIR}/dialtek_uart.o.d ${OBJECTDIR}/hamilton_pump.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main_heater.o ${OBJECTDIR}/main_steppers.o ${OBJECTDIR}/main_dosing_sys.o ${OBJECTDIR}/main_io.o ${OBJECTDIR}/d_delay.o ${OBJECTDIR}/d_eeprom.o ${OBJECTDIR}/d_heater.o ${OBJECTDIR}/d_one_wire.o ${OBJECTDIR}/d_SPI.o ${OBJECTDIR}/dialtek_modbus.o ${OBJECTDIR}/dialtek_uart.o ${OBJECTDIR}/hamilton_pump.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=main_heater.c main_steppers.c main_dosing_sys.c main_io.c d_delay.c d_eeprom.c d_heater.c d_one_wire.c d_SPI.c dialtek_modbus.c dialtek_uart.c hamilton_pump.c main.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/dialtek_controller_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MU810
MP_LINKER_FILE_OPTION=,--script=p33EP256MU810.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main_heater.o: main_heater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_heater.o.d 
	@${RM} ${OBJECTDIR}/main_heater.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_heater.c  -o ${OBJECTDIR}/main_heater.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_heater.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main_heater.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main_steppers.o: main_steppers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_steppers.o.d 
	@${RM} ${OBJECTDIR}/main_steppers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_steppers.c  -o ${OBJECTDIR}/main_steppers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_steppers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main_steppers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main_dosing_sys.o: main_dosing_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_dosing_sys.o.d 
	@${RM} ${OBJECTDIR}/main_dosing_sys.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_dosing_sys.c  -o ${OBJECTDIR}/main_dosing_sys.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_dosing_sys.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main_dosing_sys.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main_io.o: main_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_io.o.d 
	@${RM} ${OBJECTDIR}/main_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_io.c  -o ${OBJECTDIR}/main_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_io.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_delay.o: d_delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_delay.o.d 
	@${RM} ${OBJECTDIR}/d_delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_delay.c  -o ${OBJECTDIR}/d_delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_delay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_eeprom.o: d_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_eeprom.o.d 
	@${RM} ${OBJECTDIR}/d_eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_eeprom.c  -o ${OBJECTDIR}/d_eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_eeprom.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_heater.o: d_heater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_heater.o.d 
	@${RM} ${OBJECTDIR}/d_heater.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_heater.c  -o ${OBJECTDIR}/d_heater.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_heater.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_heater.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_one_wire.o: d_one_wire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_one_wire.o.d 
	@${RM} ${OBJECTDIR}/d_one_wire.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_one_wire.c  -o ${OBJECTDIR}/d_one_wire.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_one_wire.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_one_wire.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_SPI.o: d_SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_SPI.o.d 
	@${RM} ${OBJECTDIR}/d_SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_SPI.c  -o ${OBJECTDIR}/d_SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_SPI.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_SPI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dialtek_modbus.o: dialtek_modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o.d 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dialtek_modbus.c  -o ${OBJECTDIR}/dialtek_modbus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dialtek_modbus.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/dialtek_modbus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dialtek_uart.o: dialtek_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_uart.o.d 
	@${RM} ${OBJECTDIR}/dialtek_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dialtek_uart.c  -o ${OBJECTDIR}/dialtek_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dialtek_uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/dialtek_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/hamilton_pump.o: hamilton_pump.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hamilton_pump.o.d 
	@${RM} ${OBJECTDIR}/hamilton_pump.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hamilton_pump.c  -o ${OBJECTDIR}/hamilton_pump.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/hamilton_pump.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/hamilton_pump.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -mno-eds-warn  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/main_heater.o: main_heater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_heater.o.d 
	@${RM} ${OBJECTDIR}/main_heater.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_heater.c  -o ${OBJECTDIR}/main_heater.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_heater.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main_heater.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main_steppers.o: main_steppers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_steppers.o.d 
	@${RM} ${OBJECTDIR}/main_steppers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_steppers.c  -o ${OBJECTDIR}/main_steppers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_steppers.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main_steppers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main_dosing_sys.o: main_dosing_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_dosing_sys.o.d 
	@${RM} ${OBJECTDIR}/main_dosing_sys.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_dosing_sys.c  -o ${OBJECTDIR}/main_dosing_sys.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_dosing_sys.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main_dosing_sys.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main_io.o: main_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main_io.o.d 
	@${RM} ${OBJECTDIR}/main_io.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main_io.c  -o ${OBJECTDIR}/main_io.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main_io.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main_io.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_delay.o: d_delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_delay.o.d 
	@${RM} ${OBJECTDIR}/d_delay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_delay.c  -o ${OBJECTDIR}/d_delay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_delay.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_delay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_eeprom.o: d_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_eeprom.o.d 
	@${RM} ${OBJECTDIR}/d_eeprom.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_eeprom.c  -o ${OBJECTDIR}/d_eeprom.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_eeprom.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_eeprom.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_heater.o: d_heater.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_heater.o.d 
	@${RM} ${OBJECTDIR}/d_heater.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_heater.c  -o ${OBJECTDIR}/d_heater.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_heater.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_heater.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_one_wire.o: d_one_wire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_one_wire.o.d 
	@${RM} ${OBJECTDIR}/d_one_wire.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_one_wire.c  -o ${OBJECTDIR}/d_one_wire.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_one_wire.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_one_wire.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/d_SPI.o: d_SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_SPI.o.d 
	@${RM} ${OBJECTDIR}/d_SPI.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  d_SPI.c  -o ${OBJECTDIR}/d_SPI.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/d_SPI.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/d_SPI.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dialtek_modbus.o: dialtek_modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o.d 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dialtek_modbus.c  -o ${OBJECTDIR}/dialtek_modbus.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dialtek_modbus.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/dialtek_modbus.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/dialtek_uart.o: dialtek_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_uart.o.d 
	@${RM} ${OBJECTDIR}/dialtek_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  dialtek_uart.c  -o ${OBJECTDIR}/dialtek_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/dialtek_uart.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/dialtek_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/hamilton_pump.o: hamilton_pump.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/hamilton_pump.o.d 
	@${RM} ${OBJECTDIR}/hamilton_pump.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  hamilton_pump.c  -o ${OBJECTDIR}/hamilton_pump.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/hamilton_pump.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/hamilton_pump.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off   --std=gnu99
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/dialtek_controller_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dialtek_controller_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/dialtek_controller_v2.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dialtek_controller_v2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/dialtek_controller_v2.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
