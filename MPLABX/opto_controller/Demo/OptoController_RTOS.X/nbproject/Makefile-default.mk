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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OptoController_RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/OptoController_RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../Source/portable/MemMang/heap_1.c ../../Source/portable/MPLAB/PIC24_dsPIC/port.c ../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S ../../Source/list.c ../../Source/queue.c ../../Source/tasks.c ../../Source/timers.c dialtek_modbus.c dialtek_one_wire.c dialtek_uart.c d_SPI.c d_eeprom.c main.c opto_controller.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/897580706/heap_1.o ${OBJECTDIR}/_ext/410575107/port.o ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o ${OBJECTDIR}/_ext/1787047461/list.o ${OBJECTDIR}/_ext/1787047461/queue.o ${OBJECTDIR}/_ext/1787047461/tasks.o ${OBJECTDIR}/_ext/1787047461/timers.o ${OBJECTDIR}/dialtek_modbus.o ${OBJECTDIR}/dialtek_one_wire.o ${OBJECTDIR}/dialtek_uart.o ${OBJECTDIR}/d_SPI.o ${OBJECTDIR}/d_eeprom.o ${OBJECTDIR}/main.o ${OBJECTDIR}/opto_controller.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/897580706/heap_1.o.d ${OBJECTDIR}/_ext/410575107/port.o.d ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d ${OBJECTDIR}/_ext/1787047461/list.o.d ${OBJECTDIR}/_ext/1787047461/queue.o.d ${OBJECTDIR}/_ext/1787047461/tasks.o.d ${OBJECTDIR}/_ext/1787047461/timers.o.d ${OBJECTDIR}/dialtek_modbus.o.d ${OBJECTDIR}/dialtek_one_wire.o.d ${OBJECTDIR}/dialtek_uart.o.d ${OBJECTDIR}/d_SPI.o.d ${OBJECTDIR}/d_eeprom.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/opto_controller.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/897580706/heap_1.o ${OBJECTDIR}/_ext/410575107/port.o ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o ${OBJECTDIR}/_ext/1787047461/list.o ${OBJECTDIR}/_ext/1787047461/queue.o ${OBJECTDIR}/_ext/1787047461/tasks.o ${OBJECTDIR}/_ext/1787047461/timers.o ${OBJECTDIR}/dialtek_modbus.o ${OBJECTDIR}/dialtek_one_wire.o ${OBJECTDIR}/dialtek_uart.o ${OBJECTDIR}/d_SPI.o ${OBJECTDIR}/d_eeprom.o ${OBJECTDIR}/main.o ${OBJECTDIR}/opto_controller.o

# Source Files
SOURCEFILES=../../Source/portable/MemMang/heap_1.c ../../Source/portable/MPLAB/PIC24_dsPIC/port.c ../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S ../../Source/list.c ../../Source/queue.c ../../Source/tasks.c ../../Source/timers.c dialtek_modbus.c dialtek_one_wire.c dialtek_uart.c d_SPI.c d_eeprom.c main.c opto_controller.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/OptoController_RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24HJ256GP206
MP_LINKER_FILE_OPTION=,-Tp24HJ256GP206.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/410575107/portasm_PIC24.o: ../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/410575107" 
	@${RM} ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.asm.d 
	@${RM} ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.ok ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.err 
	@${RM} ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d" "${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -c -mcpu=$(MP_PROCESSOR_OPTION)   -MMD -MF "${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d"  -o ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o ../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g
	
else
${OBJECTDIR}/_ext/410575107/portasm_PIC24.o: ../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/410575107" 
	@${RM} ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.asm.d 
	@${RM} ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.ok ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.err 
	@${RM} ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d" "${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -omf=elf -c -mcpu=$(MP_PROCESSOR_OPTION)   -MMD -MF "${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d"  -o ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o ../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.asm.d",-g
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/897580706/heap_1.o: ../../Source/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897580706" 
	@${RM} ${OBJECTDIR}/_ext/897580706/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/897580706/heap_1.o.ok ${OBJECTDIR}/_ext/897580706/heap_1.o.err 
	@${RM} ${OBJECTDIR}/_ext/897580706/heap_1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897580706/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/897580706/heap_1.o.d" -o ${OBJECTDIR}/_ext/897580706/heap_1.o ../../Source/portable/MemMang/heap_1.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/410575107/port.o: ../../Source/portable/MPLAB/PIC24_dsPIC/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/410575107" 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o.ok ${OBJECTDIR}/_ext/410575107/port.o.err 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/410575107/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/410575107/port.o.d" -o ${OBJECTDIR}/_ext/410575107/port.o ../../Source/portable/MPLAB/PIC24_dsPIC/port.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/1787047461/list.o: ../../Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o.ok ${OBJECTDIR}/_ext/1787047461/list.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/list.o.d" -o ${OBJECTDIR}/_ext/1787047461/list.o ../../Source/list.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/1787047461/queue.o: ../../Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o.ok ${OBJECTDIR}/_ext/1787047461/queue.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/queue.o.d" -o ${OBJECTDIR}/_ext/1787047461/queue.o ../../Source/queue.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/1787047461/tasks.o: ../../Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o.ok ${OBJECTDIR}/_ext/1787047461/tasks.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/tasks.o.d" -o ${OBJECTDIR}/_ext/1787047461/tasks.o ../../Source/tasks.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/1787047461/timers.o: ../../Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o.ok ${OBJECTDIR}/_ext/1787047461/timers.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/timers.o.d" -o ${OBJECTDIR}/_ext/1787047461/timers.o ../../Source/timers.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/dialtek_modbus.o: dialtek_modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o.d 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o.ok ${OBJECTDIR}/dialtek_modbus.o.err 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o 
	@${FIXDEPS} "${OBJECTDIR}/dialtek_modbus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/dialtek_modbus.o.d" -o ${OBJECTDIR}/dialtek_modbus.o dialtek_modbus.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/dialtek_one_wire.o: dialtek_one_wire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_one_wire.o.d 
	@${RM} ${OBJECTDIR}/dialtek_one_wire.o.ok ${OBJECTDIR}/dialtek_one_wire.o.err 
	@${RM} ${OBJECTDIR}/dialtek_one_wire.o 
	@${FIXDEPS} "${OBJECTDIR}/dialtek_one_wire.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/dialtek_one_wire.o.d" -o ${OBJECTDIR}/dialtek_one_wire.o dialtek_one_wire.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/dialtek_uart.o: dialtek_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_uart.o.d 
	@${RM} ${OBJECTDIR}/dialtek_uart.o.ok ${OBJECTDIR}/dialtek_uart.o.err 
	@${RM} ${OBJECTDIR}/dialtek_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/dialtek_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/dialtek_uart.o.d" -o ${OBJECTDIR}/dialtek_uart.o dialtek_uart.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/d_SPI.o: d_SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_SPI.o.d 
	@${RM} ${OBJECTDIR}/d_SPI.o.ok ${OBJECTDIR}/d_SPI.o.err 
	@${RM} ${OBJECTDIR}/d_SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/d_SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/d_SPI.o.d" -o ${OBJECTDIR}/d_SPI.o d_SPI.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/d_eeprom.o: d_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_eeprom.o.d 
	@${RM} ${OBJECTDIR}/d_eeprom.o.ok ${OBJECTDIR}/d_eeprom.o.err 
	@${RM} ${OBJECTDIR}/d_eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/d_eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/d_eeprom.o.d" -o ${OBJECTDIR}/d_eeprom.o d_eeprom.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/opto_controller.o: opto_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/opto_controller.o.d 
	@${RM} ${OBJECTDIR}/opto_controller.o.ok ${OBJECTDIR}/opto_controller.o.err 
	@${RM} ${OBJECTDIR}/opto_controller.o 
	@${FIXDEPS} "${OBJECTDIR}/opto_controller.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/opto_controller.o.d" -o ${OBJECTDIR}/opto_controller.o opto_controller.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
else
${OBJECTDIR}/_ext/897580706/heap_1.o: ../../Source/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897580706" 
	@${RM} ${OBJECTDIR}/_ext/897580706/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/897580706/heap_1.o.ok ${OBJECTDIR}/_ext/897580706/heap_1.o.err 
	@${RM} ${OBJECTDIR}/_ext/897580706/heap_1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897580706/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/897580706/heap_1.o.d" -o ${OBJECTDIR}/_ext/897580706/heap_1.o ../../Source/portable/MemMang/heap_1.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/410575107/port.o: ../../Source/portable/MPLAB/PIC24_dsPIC/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/410575107" 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o.ok ${OBJECTDIR}/_ext/410575107/port.o.err 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/410575107/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/410575107/port.o.d" -o ${OBJECTDIR}/_ext/410575107/port.o ../../Source/portable/MPLAB/PIC24_dsPIC/port.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/1787047461/list.o: ../../Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o.ok ${OBJECTDIR}/_ext/1787047461/list.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/list.o.d" -o ${OBJECTDIR}/_ext/1787047461/list.o ../../Source/list.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/1787047461/queue.o: ../../Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o.ok ${OBJECTDIR}/_ext/1787047461/queue.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/queue.o.d" -o ${OBJECTDIR}/_ext/1787047461/queue.o ../../Source/queue.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/1787047461/tasks.o: ../../Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o.ok ${OBJECTDIR}/_ext/1787047461/tasks.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/tasks.o.d" -o ${OBJECTDIR}/_ext/1787047461/tasks.o ../../Source/tasks.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/_ext/1787047461/timers.o: ../../Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o.ok ${OBJECTDIR}/_ext/1787047461/timers.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/timers.o.d" -o ${OBJECTDIR}/_ext/1787047461/timers.o ../../Source/timers.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/dialtek_modbus.o: dialtek_modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o.d 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o.ok ${OBJECTDIR}/dialtek_modbus.o.err 
	@${RM} ${OBJECTDIR}/dialtek_modbus.o 
	@${FIXDEPS} "${OBJECTDIR}/dialtek_modbus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/dialtek_modbus.o.d" -o ${OBJECTDIR}/dialtek_modbus.o dialtek_modbus.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/dialtek_one_wire.o: dialtek_one_wire.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_one_wire.o.d 
	@${RM} ${OBJECTDIR}/dialtek_one_wire.o.ok ${OBJECTDIR}/dialtek_one_wire.o.err 
	@${RM} ${OBJECTDIR}/dialtek_one_wire.o 
	@${FIXDEPS} "${OBJECTDIR}/dialtek_one_wire.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/dialtek_one_wire.o.d" -o ${OBJECTDIR}/dialtek_one_wire.o dialtek_one_wire.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/dialtek_uart.o: dialtek_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/dialtek_uart.o.d 
	@${RM} ${OBJECTDIR}/dialtek_uart.o.ok ${OBJECTDIR}/dialtek_uart.o.err 
	@${RM} ${OBJECTDIR}/dialtek_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/dialtek_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/dialtek_uart.o.d" -o ${OBJECTDIR}/dialtek_uart.o dialtek_uart.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/d_SPI.o: d_SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_SPI.o.d 
	@${RM} ${OBJECTDIR}/d_SPI.o.ok ${OBJECTDIR}/d_SPI.o.err 
	@${RM} ${OBJECTDIR}/d_SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/d_SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/d_SPI.o.d" -o ${OBJECTDIR}/d_SPI.o d_SPI.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/d_eeprom.o: d_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/d_eeprom.o.d 
	@${RM} ${OBJECTDIR}/d_eeprom.o.ok ${OBJECTDIR}/d_eeprom.o.err 
	@${RM} ${OBJECTDIR}/d_eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/d_eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/d_eeprom.o.d" -o ${OBJECTDIR}/d_eeprom.o d_eeprom.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
${OBJECTDIR}/opto_controller.o: opto_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/opto_controller.o.d 
	@${RM} ${OBJECTDIR}/opto_controller.o.ok ${OBJECTDIR}/opto_controller.o.err 
	@${RM} ${OBJECTDIR}/opto_controller.o 
	@${FIXDEPS} "${OBJECTDIR}/opto_controller.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/opto_controller.o.d" -o ${OBJECTDIR}/opto_controller.o opto_controller.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra --std=gnu99 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/OptoController_RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/OptoController_RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,--stack=16,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/OptoController_RTOS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/OptoController_RTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,--stack=16,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/OptoController_RTOS.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
