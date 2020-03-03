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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC24_MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/PIC24_MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=../../Source/portable/MemMang/heap_1.c ../../Source/portable/MPLAB/PIC24_dsPIC/port.c ../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S ../../Source/list.c ../../Source/queue.c ../../Source/tasks.c ../../Source/timers.c ../../Source/croutine.c ../Common/Minimal/BlockQ.c ../Common/Minimal/blocktim.c ../Common/Minimal/comtest.c ../Common/Minimal/crflash.c ../Common/Minimal/integer.c timertest.c lcd.c main.c serial/serial.c ParTest/ParTest.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/897580706/heap_1.o ${OBJECTDIR}/_ext/410575107/port.o ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o ${OBJECTDIR}/_ext/1787047461/list.o ${OBJECTDIR}/_ext/1787047461/queue.o ${OBJECTDIR}/_ext/1787047461/tasks.o ${OBJECTDIR}/_ext/1787047461/timers.o ${OBJECTDIR}/_ext/1787047461/croutine.o ${OBJECTDIR}/_ext/270959020/BlockQ.o ${OBJECTDIR}/_ext/270959020/blocktim.o ${OBJECTDIR}/_ext/270959020/comtest.o ${OBJECTDIR}/_ext/270959020/crflash.o ${OBJECTDIR}/_ext/270959020/integer.o ${OBJECTDIR}/timertest.o ${OBJECTDIR}/lcd.o ${OBJECTDIR}/main.o ${OBJECTDIR}/serial/serial.o ${OBJECTDIR}/ParTest/ParTest.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/897580706/heap_1.o.d ${OBJECTDIR}/_ext/410575107/port.o.d ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d ${OBJECTDIR}/_ext/1787047461/list.o.d ${OBJECTDIR}/_ext/1787047461/queue.o.d ${OBJECTDIR}/_ext/1787047461/tasks.o.d ${OBJECTDIR}/_ext/1787047461/timers.o.d ${OBJECTDIR}/_ext/1787047461/croutine.o.d ${OBJECTDIR}/_ext/270959020/BlockQ.o.d ${OBJECTDIR}/_ext/270959020/blocktim.o.d ${OBJECTDIR}/_ext/270959020/comtest.o.d ${OBJECTDIR}/_ext/270959020/crflash.o.d ${OBJECTDIR}/_ext/270959020/integer.o.d ${OBJECTDIR}/timertest.o.d ${OBJECTDIR}/lcd.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/serial/serial.o.d ${OBJECTDIR}/ParTest/ParTest.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/897580706/heap_1.o ${OBJECTDIR}/_ext/410575107/port.o ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o ${OBJECTDIR}/_ext/1787047461/list.o ${OBJECTDIR}/_ext/1787047461/queue.o ${OBJECTDIR}/_ext/1787047461/tasks.o ${OBJECTDIR}/_ext/1787047461/timers.o ${OBJECTDIR}/_ext/1787047461/croutine.o ${OBJECTDIR}/_ext/270959020/BlockQ.o ${OBJECTDIR}/_ext/270959020/blocktim.o ${OBJECTDIR}/_ext/270959020/comtest.o ${OBJECTDIR}/_ext/270959020/crflash.o ${OBJECTDIR}/_ext/270959020/integer.o ${OBJECTDIR}/timertest.o ${OBJECTDIR}/lcd.o ${OBJECTDIR}/main.o ${OBJECTDIR}/serial/serial.o ${OBJECTDIR}/ParTest/ParTest.o

# Source Files
SOURCEFILES=../../Source/portable/MemMang/heap_1.c ../../Source/portable/MPLAB/PIC24_dsPIC/port.c ../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S ../../Source/list.c ../../Source/queue.c ../../Source/tasks.c ../../Source/timers.c ../../Source/croutine.c ../Common/Minimal/BlockQ.c ../Common/Minimal/blocktim.c ../Common/Minimal/comtest.c ../Common/Minimal/crflash.c ../Common/Minimal/integer.c timertest.c lcd.c main.c serial/serial.c ParTest/ParTest.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/PIC24_MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP256MU810
MP_LINKER_FILE_OPTION=,-Tp33EP256MU810.gld
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
	@${FIXDEPS} "${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d" "${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -c -mcpu=$(MP_PROCESSOR_OPTION)   -MMD -MF "${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.d"  -o ${OBJECTDIR}/_ext/410575107/portasm_PIC24.o ../../Source/portable/MPLAB/PIC24_dsPIC/portasm_PIC24.S  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/410575107/portasm_PIC24.o.asm.d",--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1,-g
	
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
	@${FIXDEPS} "${OBJECTDIR}/_ext/897580706/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/897580706/heap_1.o.d" -o ${OBJECTDIR}/_ext/897580706/heap_1.o ../../Source/portable/MemMang/heap_1.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/410575107/port.o: ../../Source/portable/MPLAB/PIC24_dsPIC/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/410575107" 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o.ok ${OBJECTDIR}/_ext/410575107/port.o.err 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/410575107/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/410575107/port.o.d" -o ${OBJECTDIR}/_ext/410575107/port.o ../../Source/portable/MPLAB/PIC24_dsPIC/port.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/list.o: ../../Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o.ok ${OBJECTDIR}/_ext/1787047461/list.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/list.o.d" -o ${OBJECTDIR}/_ext/1787047461/list.o ../../Source/list.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/queue.o: ../../Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o.ok ${OBJECTDIR}/_ext/1787047461/queue.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/queue.o.d" -o ${OBJECTDIR}/_ext/1787047461/queue.o ../../Source/queue.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/tasks.o: ../../Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o.ok ${OBJECTDIR}/_ext/1787047461/tasks.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/tasks.o.d" -o ${OBJECTDIR}/_ext/1787047461/tasks.o ../../Source/tasks.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/timers.o: ../../Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o.ok ${OBJECTDIR}/_ext/1787047461/timers.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/timers.o.d" -o ${OBJECTDIR}/_ext/1787047461/timers.o ../../Source/timers.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/croutine.o: ../../Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/croutine.o.ok ${OBJECTDIR}/_ext/1787047461/croutine.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/croutine.o.d" -o ${OBJECTDIR}/_ext/1787047461/croutine.o ../../Source/croutine.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/BlockQ.o: ../Common/Minimal/BlockQ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/BlockQ.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/BlockQ.o.ok ${OBJECTDIR}/_ext/270959020/BlockQ.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/BlockQ.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/BlockQ.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/BlockQ.o.d" -o ${OBJECTDIR}/_ext/270959020/BlockQ.o ../Common/Minimal/BlockQ.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/blocktim.o: ../Common/Minimal/blocktim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/blocktim.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/blocktim.o.ok ${OBJECTDIR}/_ext/270959020/blocktim.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/blocktim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/blocktim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/blocktim.o.d" -o ${OBJECTDIR}/_ext/270959020/blocktim.o ../Common/Minimal/blocktim.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/comtest.o: ../Common/Minimal/comtest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/comtest.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/comtest.o.ok ${OBJECTDIR}/_ext/270959020/comtest.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/comtest.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/comtest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/comtest.o.d" -o ${OBJECTDIR}/_ext/270959020/comtest.o ../Common/Minimal/comtest.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/crflash.o: ../Common/Minimal/crflash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/crflash.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/crflash.o.ok ${OBJECTDIR}/_ext/270959020/crflash.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/crflash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/crflash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/crflash.o.d" -o ${OBJECTDIR}/_ext/270959020/crflash.o ../Common/Minimal/crflash.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/integer.o: ../Common/Minimal/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/integer.o.ok ${OBJECTDIR}/_ext/270959020/integer.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/integer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/integer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/integer.o.d" -o ${OBJECTDIR}/_ext/270959020/integer.o ../Common/Minimal/integer.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/timertest.o: timertest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timertest.o.d 
	@${RM} ${OBJECTDIR}/timertest.o.ok ${OBJECTDIR}/timertest.o.err 
	@${RM} ${OBJECTDIR}/timertest.o 
	@${FIXDEPS} "${OBJECTDIR}/timertest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/timertest.o.d" -o ${OBJECTDIR}/timertest.o timertest.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/lcd.o: lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd.o.d 
	@${RM} ${OBJECTDIR}/lcd.o.ok ${OBJECTDIR}/lcd.o.err 
	@${RM} ${OBJECTDIR}/lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/lcd.o.d" -o ${OBJECTDIR}/lcd.o lcd.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/serial/serial.o: serial/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/serial" 
	@${RM} ${OBJECTDIR}/serial/serial.o.d 
	@${RM} ${OBJECTDIR}/serial/serial.o.ok ${OBJECTDIR}/serial/serial.o.err 
	@${RM} ${OBJECTDIR}/serial/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/serial/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/serial/serial.o.d" -o ${OBJECTDIR}/serial/serial.o serial/serial.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/ParTest/ParTest.o: ParTest/ParTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ParTest" 
	@${RM} ${OBJECTDIR}/ParTest/ParTest.o.d 
	@${RM} ${OBJECTDIR}/ParTest/ParTest.o.ok ${OBJECTDIR}/ParTest/ParTest.o.err 
	@${RM} ${OBJECTDIR}/ParTest/ParTest.o 
	@${FIXDEPS} "${OBJECTDIR}/ParTest/ParTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/ParTest/ParTest.o.d" -o ${OBJECTDIR}/ParTest/ParTest.o ParTest/ParTest.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
else
${OBJECTDIR}/_ext/897580706/heap_1.o: ../../Source/portable/MemMang/heap_1.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/897580706" 
	@${RM} ${OBJECTDIR}/_ext/897580706/heap_1.o.d 
	@${RM} ${OBJECTDIR}/_ext/897580706/heap_1.o.ok ${OBJECTDIR}/_ext/897580706/heap_1.o.err 
	@${RM} ${OBJECTDIR}/_ext/897580706/heap_1.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/897580706/heap_1.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/897580706/heap_1.o.d" -o ${OBJECTDIR}/_ext/897580706/heap_1.o ../../Source/portable/MemMang/heap_1.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/410575107/port.o: ../../Source/portable/MPLAB/PIC24_dsPIC/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/410575107" 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o.ok ${OBJECTDIR}/_ext/410575107/port.o.err 
	@${RM} ${OBJECTDIR}/_ext/410575107/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/410575107/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/410575107/port.o.d" -o ${OBJECTDIR}/_ext/410575107/port.o ../../Source/portable/MPLAB/PIC24_dsPIC/port.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/list.o: ../../Source/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o.ok ${OBJECTDIR}/_ext/1787047461/list.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/list.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/list.o.d" -o ${OBJECTDIR}/_ext/1787047461/list.o ../../Source/list.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/queue.o: ../../Source/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o.ok ${OBJECTDIR}/_ext/1787047461/queue.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/queue.o.d" -o ${OBJECTDIR}/_ext/1787047461/queue.o ../../Source/queue.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/tasks.o: ../../Source/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o.ok ${OBJECTDIR}/_ext/1787047461/tasks.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/tasks.o.d" -o ${OBJECTDIR}/_ext/1787047461/tasks.o ../../Source/tasks.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/timers.o: ../../Source/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o.ok ${OBJECTDIR}/_ext/1787047461/timers.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/timers.o.d" -o ${OBJECTDIR}/_ext/1787047461/timers.o ../../Source/timers.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/1787047461/croutine.o: ../../Source/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1787047461" 
	@${RM} ${OBJECTDIR}/_ext/1787047461/croutine.o.d 
	@${RM} ${OBJECTDIR}/_ext/1787047461/croutine.o.ok ${OBJECTDIR}/_ext/1787047461/croutine.o.err 
	@${RM} ${OBJECTDIR}/_ext/1787047461/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/1787047461/croutine.o.d" -o ${OBJECTDIR}/_ext/1787047461/croutine.o ../../Source/croutine.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/BlockQ.o: ../Common/Minimal/BlockQ.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/BlockQ.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/BlockQ.o.ok ${OBJECTDIR}/_ext/270959020/BlockQ.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/BlockQ.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/BlockQ.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/BlockQ.o.d" -o ${OBJECTDIR}/_ext/270959020/BlockQ.o ../Common/Minimal/BlockQ.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/blocktim.o: ../Common/Minimal/blocktim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/blocktim.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/blocktim.o.ok ${OBJECTDIR}/_ext/270959020/blocktim.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/blocktim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/blocktim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/blocktim.o.d" -o ${OBJECTDIR}/_ext/270959020/blocktim.o ../Common/Minimal/blocktim.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/comtest.o: ../Common/Minimal/comtest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/comtest.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/comtest.o.ok ${OBJECTDIR}/_ext/270959020/comtest.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/comtest.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/comtest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/comtest.o.d" -o ${OBJECTDIR}/_ext/270959020/comtest.o ../Common/Minimal/comtest.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/crflash.o: ../Common/Minimal/crflash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/crflash.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/crflash.o.ok ${OBJECTDIR}/_ext/270959020/crflash.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/crflash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/crflash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/crflash.o.d" -o ${OBJECTDIR}/_ext/270959020/crflash.o ../Common/Minimal/crflash.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/_ext/270959020/integer.o: ../Common/Minimal/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/270959020" 
	@${RM} ${OBJECTDIR}/_ext/270959020/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/270959020/integer.o.ok ${OBJECTDIR}/_ext/270959020/integer.o.err 
	@${RM} ${OBJECTDIR}/_ext/270959020/integer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/270959020/integer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/_ext/270959020/integer.o.d" -o ${OBJECTDIR}/_ext/270959020/integer.o ../Common/Minimal/integer.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/timertest.o: timertest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timertest.o.d 
	@${RM} ${OBJECTDIR}/timertest.o.ok ${OBJECTDIR}/timertest.o.err 
	@${RM} ${OBJECTDIR}/timertest.o 
	@${FIXDEPS} "${OBJECTDIR}/timertest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/timertest.o.d" -o ${OBJECTDIR}/timertest.o timertest.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/lcd.o: lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/lcd.o.d 
	@${RM} ${OBJECTDIR}/lcd.o.ok ${OBJECTDIR}/lcd.o.err 
	@${RM} ${OBJECTDIR}/lcd.o 
	@${FIXDEPS} "${OBJECTDIR}/lcd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/lcd.o.d" -o ${OBJECTDIR}/lcd.o lcd.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o.ok ${OBJECTDIR}/main.o.err 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/serial/serial.o: serial/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/serial" 
	@${RM} ${OBJECTDIR}/serial/serial.o.d 
	@${RM} ${OBJECTDIR}/serial/serial.o.ok ${OBJECTDIR}/serial/serial.o.err 
	@${RM} ${OBJECTDIR}/serial/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/serial/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/serial/serial.o.d" -o ${OBJECTDIR}/serial/serial.o serial/serial.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
${OBJECTDIR}/ParTest/ParTest.o: ParTest/ParTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/ParTest" 
	@${RM} ${OBJECTDIR}/ParTest/ParTest.o.d 
	@${RM} ${OBJECTDIR}/ParTest/ParTest.o.ok ${OBJECTDIR}/ParTest/ParTest.o.err 
	@${RM} ${OBJECTDIR}/ParTest/ParTest.o 
	@${FIXDEPS} "${OBJECTDIR}/ParTest/ParTest.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -omf=elf -x c -c -mcpu=$(MP_PROCESSOR_OPTION) -ffunction-sections -Wall -MMD -MF "${OBJECTDIR}/ParTest/ParTest.o.d" -o ${OBJECTDIR}/ParTest/ParTest.o ParTest/ParTest.c     -I ../../Source/include -I ../../Source/portable/MPLAB/PIC24_dsPIC -I ../Common/include -I . -Wextra
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/PIC24_MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_SIMULATOR=1 -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC24_MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,--stack=16,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_SIMULATOR=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/PIC24_MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -omf=elf -mcpu=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/PIC24_MPLAB.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1,--stack=16,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}\\pic30-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/PIC24_MPLAB.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -omf=elf
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
