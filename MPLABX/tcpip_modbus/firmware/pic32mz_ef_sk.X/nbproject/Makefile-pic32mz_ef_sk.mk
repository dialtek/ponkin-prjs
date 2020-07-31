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
ifeq "$(wildcard nbproject/Makefile-local-pic32mz_ef_sk.mk)" "nbproject/Makefile-local-pic32mz_ef_sk.mk"
include nbproject/Makefile-local-pic32mz_ef_sk.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=pic32mz_ef_sk
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
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
SOURCEFILES_QUOTED_IF_SPACED=../src/config/pic32mz_ef_sk/bsp/bsp.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c ../src/config/pic32mz_ef_sk/tasks.c ../src/config/pic32mz_ef_sk/initialization.c ../src/config/pic32mz_ef_sk/interrupts.c ../src/config/pic32mz_ef_sk/exceptions.c ../src/app.c ../src/main.c ../src/modbus/dialtek_modbus.c ../src/tcp_app.c ../src/modbus_buf.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/978308758/bsp.o ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o ${OBJECTDIR}/_ext/138020607/drv_ethphy.o ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o ${OBJECTDIR}/_ext/1761147401/drv_miim.o ${OBJECTDIR}/_ext/2027382860/helpers.o ${OBJECTDIR}/_ext/2027382860/dns.o ${OBJECTDIR}/_ext/2027382860/icmp.o ${OBJECTDIR}/_ext/2027382860/tcp.o ${OBJECTDIR}/_ext/2027382860/dhcp.o ${OBJECTDIR}/_ext/2027382860/arp.o ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o ${OBJECTDIR}/_ext/2027382860/ipv4.o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o ${OBJECTDIR}/_ext/2027382860/hash_fnv.o ${OBJECTDIR}/_ext/2027382860/oahash.o ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o ${OBJECTDIR}/_ext/2027382860/udp.o ${OBJECTDIR}/_ext/1098417660/plib_clk.o ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o ${OBJECTDIR}/_ext/308860137/plib_evic.o ${OBJECTDIR}/_ext/308913965/plib_gpio.o ${OBJECTDIR}/_ext/309316908/plib_uart2.o ${OBJECTDIR}/_ext/458842868/xc32_monitor.o ${OBJECTDIR}/_ext/2135388491/sys_command.o ${OBJECTDIR}/_ext/1702866625/sys_console.o ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o ${OBJECTDIR}/_ext/57023747/sys_debug.o ${OBJECTDIR}/_ext/723085273/sys_int.o ${OBJECTDIR}/_ext/1658225107/sys_time.o ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o ${OBJECTDIR}/_ext/942849350/tasks.o ${OBJECTDIR}/_ext/942849350/initialization.o ${OBJECTDIR}/_ext/942849350/interrupts.o ${OBJECTDIR}/_ext/942849350/exceptions.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o ${OBJECTDIR}/_ext/1360937237/tcp_app.o ${OBJECTDIR}/_ext/1360937237/modbus_buf.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/978308758/bsp.o.d ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d ${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d ${OBJECTDIR}/_ext/1761147401/drv_miim.o.d ${OBJECTDIR}/_ext/2027382860/helpers.o.d ${OBJECTDIR}/_ext/2027382860/dns.o.d ${OBJECTDIR}/_ext/2027382860/icmp.o.d ${OBJECTDIR}/_ext/2027382860/tcp.o.d ${OBJECTDIR}/_ext/2027382860/dhcp.o.d ${OBJECTDIR}/_ext/2027382860/arp.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d ${OBJECTDIR}/_ext/2027382860/ipv4.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d ${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d ${OBJECTDIR}/_ext/2027382860/oahash.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d ${OBJECTDIR}/_ext/2027382860/udp.o.d ${OBJECTDIR}/_ext/1098417660/plib_clk.o.d ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d ${OBJECTDIR}/_ext/308860137/plib_evic.o.d ${OBJECTDIR}/_ext/308913965/plib_gpio.o.d ${OBJECTDIR}/_ext/309316908/plib_uart2.o.d ${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d ${OBJECTDIR}/_ext/2135388491/sys_command.o.d ${OBJECTDIR}/_ext/1702866625/sys_console.o.d ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d ${OBJECTDIR}/_ext/57023747/sys_debug.o.d ${OBJECTDIR}/_ext/723085273/sys_int.o.d ${OBJECTDIR}/_ext/1658225107/sys_time.o.d ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d ${OBJECTDIR}/_ext/942849350/tasks.o.d ${OBJECTDIR}/_ext/942849350/initialization.o.d ${OBJECTDIR}/_ext/942849350/interrupts.o.d ${OBJECTDIR}/_ext/942849350/exceptions.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d ${OBJECTDIR}/_ext/1360937237/tcp_app.o.d ${OBJECTDIR}/_ext/1360937237/modbus_buf.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/978308758/bsp.o ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o ${OBJECTDIR}/_ext/138020607/drv_ethphy.o ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o ${OBJECTDIR}/_ext/1761147401/drv_miim.o ${OBJECTDIR}/_ext/2027382860/helpers.o ${OBJECTDIR}/_ext/2027382860/dns.o ${OBJECTDIR}/_ext/2027382860/icmp.o ${OBJECTDIR}/_ext/2027382860/tcp.o ${OBJECTDIR}/_ext/2027382860/dhcp.o ${OBJECTDIR}/_ext/2027382860/arp.o ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o ${OBJECTDIR}/_ext/2027382860/ipv4.o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o ${OBJECTDIR}/_ext/2027382860/hash_fnv.o ${OBJECTDIR}/_ext/2027382860/oahash.o ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o ${OBJECTDIR}/_ext/2027382860/udp.o ${OBJECTDIR}/_ext/1098417660/plib_clk.o ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o ${OBJECTDIR}/_ext/308860137/plib_evic.o ${OBJECTDIR}/_ext/308913965/plib_gpio.o ${OBJECTDIR}/_ext/309316908/plib_uart2.o ${OBJECTDIR}/_ext/458842868/xc32_monitor.o ${OBJECTDIR}/_ext/2135388491/sys_command.o ${OBJECTDIR}/_ext/1702866625/sys_console.o ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o ${OBJECTDIR}/_ext/57023747/sys_debug.o ${OBJECTDIR}/_ext/723085273/sys_int.o ${OBJECTDIR}/_ext/1658225107/sys_time.o ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o ${OBJECTDIR}/_ext/942849350/tasks.o ${OBJECTDIR}/_ext/942849350/initialization.o ${OBJECTDIR}/_ext/942849350/interrupts.o ${OBJECTDIR}/_ext/942849350/exceptions.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o ${OBJECTDIR}/_ext/1360937237/tcp_app.o ${OBJECTDIR}/_ext/1360937237/modbus_buf.o

# Source Files
SOURCEFILES=../src/config/pic32mz_ef_sk/bsp/bsp.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c ../src/config/pic32mz_ef_sk/tasks.c ../src/config/pic32mz_ef_sk/initialization.c ../src/config/pic32mz_ef_sk/interrupts.c ../src/config/pic32mz_ef_sk/exceptions.c ../src/app.c ../src/main.c ../src/modbus/dialtek_modbus.c ../src/tcp_app.c ../src/modbus_buf.c



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
	${MAKE}  -f nbproject/Makefile-pic32mz_ef_sk.mk dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MZ2048EFH144
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.ok ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d" "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S  -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.ok ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d" "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S  -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/978308758/bsp.o: ../src/config/pic32mz_ef_sk/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/978308758" 
	@${RM} ${OBJECTDIR}/_ext/978308758/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/978308758/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/978308758/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/978308758/bsp.o.d" -o ${OBJECTDIR}/_ext/978308758/bsp.o ../src/config/pic32mz_ef_sk/bsp/bsp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1314174413/drv_ethmac.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/138020607/drv_ethphy.o: ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/138020607" 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_ethphy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d" -o ${OBJECTDIR}/_ext/138020607/drv_ethphy.o ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o: ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/138020607" 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d" -o ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1761147401/drv_miim.o: ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1761147401" 
	@${RM} ${OBJECTDIR}/_ext/1761147401/drv_miim.o.d 
	@${RM} ${OBJECTDIR}/_ext/1761147401/drv_miim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1761147401/drv_miim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1761147401/drv_miim.o.d" -o ${OBJECTDIR}/_ext/1761147401/drv_miim.o ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/helpers.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/helpers.o.d" -o ${OBJECTDIR}/_ext/2027382860/helpers.o ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/dns.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/dns.o.d" -o ${OBJECTDIR}/_ext/2027382860/dns.o ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/icmp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/icmp.o.d" -o ${OBJECTDIR}/_ext/2027382860/icmp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcp.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/dhcp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dhcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dhcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/dhcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/dhcp.o.d" -o ${OBJECTDIR}/_ext/2027382860/dhcp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/arp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/arp.o.d" -o ${OBJECTDIR}/_ext/2027382860/arp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_commands.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/ipv4.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/ipv4.o.d" -o ${OBJECTDIR}/_ext/2027382860/ipv4.o ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/hash_fnv.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/hash_fnv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d" -o ${OBJECTDIR}/_ext/2027382860/hash_fnv.o ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/oahash.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/oahash.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/oahash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/oahash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/oahash.o.d" -o ${OBJECTDIR}/_ext/2027382860/oahash.o ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_manager.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_notify.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_packet.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/udp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/udp.o.d" -o ${OBJECTDIR}/_ext/2027382860/udp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1098417660/plib_clk.o: ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1098417660" 
	@${RM} ${OBJECTDIR}/_ext/1098417660/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1098417660/plib_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1098417660/plib_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1098417660/plib_clk.o.d" -o ${OBJECTDIR}/_ext/1098417660/plib_clk.o ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1710852712/plib_coretimer.o: ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1710852712" 
	@${RM} ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/308860137/plib_evic.o: ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/308860137" 
	@${RM} ${OBJECTDIR}/_ext/308860137/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/308860137/plib_evic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/308860137/plib_evic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/308860137/plib_evic.o.d" -o ${OBJECTDIR}/_ext/308860137/plib_evic.o ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/308913965/plib_gpio.o: ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/308913965" 
	@${RM} ${OBJECTDIR}/_ext/308913965/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/308913965/plib_gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/308913965/plib_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/308913965/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/308913965/plib_gpio.o ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/309316908/plib_uart2.o: ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/309316908" 
	@${RM} ${OBJECTDIR}/_ext/309316908/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/309316908/plib_uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/309316908/plib_uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/309316908/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/309316908/plib_uart2.o ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/458842868/xc32_monitor.o: ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/458842868" 
	@${RM} ${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/458842868/xc32_monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/458842868/xc32_monitor.o ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2135388491/sys_command.o: ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2135388491" 
	@${RM} ${OBJECTDIR}/_ext/2135388491/sys_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/2135388491/sys_command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2135388491/sys_command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2135388491/sys_command.o.d" -o ${OBJECTDIR}/_ext/2135388491/sys_command.o ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1702866625/sys_console.o: ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1702866625" 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1702866625/sys_console.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1702866625/sys_console.o.d" -o ${OBJECTDIR}/_ext/1702866625/sys_console.o ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1702866625/sys_console_uart.o: ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1702866625" 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/57023747/sys_debug.o: ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/57023747" 
	@${RM} ${OBJECTDIR}/_ext/57023747/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/57023747/sys_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/57023747/sys_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/57023747/sys_debug.o.d" -o ${OBJECTDIR}/_ext/57023747/sys_debug.o ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/723085273/sys_int.o: ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/723085273" 
	@${RM} ${OBJECTDIR}/_ext/723085273/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/723085273/sys_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/723085273/sys_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/723085273/sys_int.o.d" -o ${OBJECTDIR}/_ext/723085273/sys_int.o ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1658225107/sys_time.o: ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1658225107" 
	@${RM} ${OBJECTDIR}/_ext/1658225107/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1658225107/sys_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1658225107/sys_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1658225107/sys_time.o.d" -o ${OBJECTDIR}/_ext/1658225107/sys_time.o ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o: ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344301860" 
	@${RM} ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d" -o ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/942849350/tasks.o: ../src/config/pic32mz_ef_sk/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/942849350/tasks.o.d" -o ${OBJECTDIR}/_ext/942849350/tasks.o ../src/config/pic32mz_ef_sk/tasks.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/942849350/initialization.o: ../src/config/pic32mz_ef_sk/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/initialization.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/942849350/initialization.o.d" -o ${OBJECTDIR}/_ext/942849350/initialization.o ../src/config/pic32mz_ef_sk/initialization.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/942849350/interrupts.o: ../src/config/pic32mz_ef_sk/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/942849350/interrupts.o.d" -o ${OBJECTDIR}/_ext/942849350/interrupts.o ../src/config/pic32mz_ef_sk/interrupts.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/942849350/exceptions.o: ../src/config/pic32mz_ef_sk/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/942849350/exceptions.o.d" -o ${OBJECTDIR}/_ext/942849350/exceptions.o ../src/config/pic32mz_ef_sk/exceptions.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/108032392/dialtek_modbus.o: ../src/modbus/dialtek_modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/108032392" 
	@${RM} ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d 
	@${RM} ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d" -o ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o ../src/modbus/dialtek_modbus.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/tcp_app.o: ../src/tcp_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tcp_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tcp_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/tcp_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/tcp_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/tcp_app.o ../src/tcp_app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/modbus_buf.o: ../src/modbus_buf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_buf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_buf.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/modbus_buf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/modbus_buf.o.d" -o ${OBJECTDIR}/_ext/1360937237/modbus_buf.o ../src/modbus_buf.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/_ext/978308758/bsp.o: ../src/config/pic32mz_ef_sk/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/978308758" 
	@${RM} ${OBJECTDIR}/_ext/978308758/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/978308758/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/978308758/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/978308758/bsp.o.d" -o ${OBJECTDIR}/_ext/978308758/bsp.o ../src/config/pic32mz_ef_sk/bsp/bsp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1314174413/drv_ethmac.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/138020607/drv_ethphy.o: ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/138020607" 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_ethphy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d" -o ${OBJECTDIR}/_ext/138020607/drv_ethphy.o ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o: ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/138020607" 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d" -o ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1761147401/drv_miim.o: ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1761147401" 
	@${RM} ${OBJECTDIR}/_ext/1761147401/drv_miim.o.d 
	@${RM} ${OBJECTDIR}/_ext/1761147401/drv_miim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1761147401/drv_miim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1761147401/drv_miim.o.d" -o ${OBJECTDIR}/_ext/1761147401/drv_miim.o ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/helpers.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/helpers.o.d" -o ${OBJECTDIR}/_ext/2027382860/helpers.o ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/dns.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/dns.o.d" -o ${OBJECTDIR}/_ext/2027382860/dns.o ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/icmp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/icmp.o.d" -o ${OBJECTDIR}/_ext/2027382860/icmp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcp.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/dhcp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dhcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dhcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/dhcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/dhcp.o.d" -o ${OBJECTDIR}/_ext/2027382860/dhcp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/arp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/arp.o.d" -o ${OBJECTDIR}/_ext/2027382860/arp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_commands.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/ipv4.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/ipv4.o.d" -o ${OBJECTDIR}/_ext/2027382860/ipv4.o ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/hash_fnv.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/hash_fnv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d" -o ${OBJECTDIR}/_ext/2027382860/hash_fnv.o ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/oahash.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/oahash.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/oahash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/oahash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/oahash.o.d" -o ${OBJECTDIR}/_ext/2027382860/oahash.o ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_manager.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_notify.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/tcpip_packet.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2027382860/udp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2027382860/udp.o.d" -o ${OBJECTDIR}/_ext/2027382860/udp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1098417660/plib_clk.o: ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1098417660" 
	@${RM} ${OBJECTDIR}/_ext/1098417660/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1098417660/plib_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1098417660/plib_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1098417660/plib_clk.o.d" -o ${OBJECTDIR}/_ext/1098417660/plib_clk.o ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1710852712/plib_coretimer.o: ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1710852712" 
	@${RM} ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/308860137/plib_evic.o: ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/308860137" 
	@${RM} ${OBJECTDIR}/_ext/308860137/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/308860137/plib_evic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/308860137/plib_evic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/308860137/plib_evic.o.d" -o ${OBJECTDIR}/_ext/308860137/plib_evic.o ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/308913965/plib_gpio.o: ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/308913965" 
	@${RM} ${OBJECTDIR}/_ext/308913965/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/308913965/plib_gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/308913965/plib_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/308913965/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/308913965/plib_gpio.o ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/309316908/plib_uart2.o: ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/309316908" 
	@${RM} ${OBJECTDIR}/_ext/309316908/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/309316908/plib_uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/309316908/plib_uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/309316908/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/309316908/plib_uart2.o ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/458842868/xc32_monitor.o: ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/458842868" 
	@${RM} ${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/458842868/xc32_monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/458842868/xc32_monitor.o ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/2135388491/sys_command.o: ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2135388491" 
	@${RM} ${OBJECTDIR}/_ext/2135388491/sys_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/2135388491/sys_command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2135388491/sys_command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/2135388491/sys_command.o.d" -o ${OBJECTDIR}/_ext/2135388491/sys_command.o ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1702866625/sys_console.o: ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1702866625" 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1702866625/sys_console.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1702866625/sys_console.o.d" -o ${OBJECTDIR}/_ext/1702866625/sys_console.o ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1702866625/sys_console_uart.o: ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1702866625" 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/57023747/sys_debug.o: ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/57023747" 
	@${RM} ${OBJECTDIR}/_ext/57023747/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/57023747/sys_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/57023747/sys_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/57023747/sys_debug.o.d" -o ${OBJECTDIR}/_ext/57023747/sys_debug.o ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/723085273/sys_int.o: ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/723085273" 
	@${RM} ${OBJECTDIR}/_ext/723085273/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/723085273/sys_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/723085273/sys_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/723085273/sys_int.o.d" -o ${OBJECTDIR}/_ext/723085273/sys_int.o ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1658225107/sys_time.o: ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1658225107" 
	@${RM} ${OBJECTDIR}/_ext/1658225107/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1658225107/sys_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1658225107/sys_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1658225107/sys_time.o.d" -o ${OBJECTDIR}/_ext/1658225107/sys_time.o ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o: ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344301860" 
	@${RM} ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d" -o ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/942849350/tasks.o: ../src/config/pic32mz_ef_sk/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/942849350/tasks.o.d" -o ${OBJECTDIR}/_ext/942849350/tasks.o ../src/config/pic32mz_ef_sk/tasks.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/942849350/initialization.o: ../src/config/pic32mz_ef_sk/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/initialization.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/942849350/initialization.o.d" -o ${OBJECTDIR}/_ext/942849350/initialization.o ../src/config/pic32mz_ef_sk/initialization.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/942849350/interrupts.o: ../src/config/pic32mz_ef_sk/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/942849350/interrupts.o.d" -o ${OBJECTDIR}/_ext/942849350/interrupts.o ../src/config/pic32mz_ef_sk/interrupts.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/942849350/exceptions.o: ../src/config/pic32mz_ef_sk/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/942849350/exceptions.o.d" -o ${OBJECTDIR}/_ext/942849350/exceptions.o ../src/config/pic32mz_ef_sk/exceptions.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/108032392/dialtek_modbus.o: ../src/modbus/dialtek_modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/108032392" 
	@${RM} ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d 
	@${RM} ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d" -o ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o ../src/modbus/dialtek_modbus.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/tcp_app.o: ../src/tcp_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tcp_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/tcp_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/tcp_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/tcp_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/tcp_app.o ../src/tcp_app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/1360937237/modbus_buf.o: ../src/modbus_buf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_buf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_buf.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/modbus_buf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -O1 -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFH144_DFP" -I"../src/mips" -Werror -Wall -MMD -MF "${OBJECTDIR}/_ext/1360937237/modbus_buf.o.d" -o ${OBJECTDIR}/_ext/1360937237/modbus_buf.o ../src/modbus_buf.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=64960,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=64960,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/pic32mz_ef_sk
	${RM} -r dist/pic32mz_ef_sk

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
