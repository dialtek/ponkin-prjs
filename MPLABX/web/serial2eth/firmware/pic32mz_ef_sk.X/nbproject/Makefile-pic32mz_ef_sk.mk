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
SOURCEFILES_QUOTED_IF_SPACED=../src/third_party/wolfssl/wolfssl/wolfcrypt/src/misc.c ../src/config/pic32mz_ef_sk/bsp/bsp.c ../src/config/pic32mz_ef_sk/crypto/src/crypto.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory.c ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_file_system.c ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_nvm.c ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c ../src/config/pic32mz_ef_sk/library/tcpip/src/common/sys_fs_shell.c ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/nbns.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/icmpv6.c ../src/config/pic32mz_ef_sk/library/tcpip/src/ndp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv6.c ../src/config/pic32mz_ef_sk/library/tcpip/src/http.c ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c ../src/config/pic32mz_ef_sk/library/tcpip/src/smtpc.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c ../src/config/pic32mz_ef_sk/library/tcpip/src/sntp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_announce.c ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c ../src/config/pic32mz_ef_sk/net_pres/pres/src/net_pres.c ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_enc_glue.c ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_cert_store.c ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c ../src/config/pic32mz_ef_sk/peripheral/nvm/plib_nvm.c ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/ff.c ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/diskio.c ../src/config/pic32mz_ef_sk/system/fs/mpfs/src/mpfs.c ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs.c ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs_media_manager.c ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c ../src/config/pic32mz_ef_sk/tasks.c ../src/config/pic32mz_ef_sk/initialization.c ../src/config/pic32mz_ef_sk/interrupts.c ../src/config/pic32mz_ef_sk/exceptions.c ../src/modbus/dialtek_modbus.c ../src/modbus_app.c ../src/modbus_buf_tcp.c ../src/PIC32MZ_SPI.c ../src/d_eeprom.c ../src/PIC32MZ_UART.c ../src/mpfs_img2.c ../src/http_print.c ../src/custom_http_app.c ../src/http_app.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/pic32mz-crypt.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_sam6149.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_u2238.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_ecc_pukcl.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_pukcl_functions.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_sam6334.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_u2242.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rsa_pukcl.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam11105.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam11105.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam11105.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha384_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha512_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_tdes_sam6150.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_wolfcryptcb.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/arc4.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asm.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asn.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2b.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2s.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/camellia.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha20_poly1305.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cmac.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/coding.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/compress.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cpuid.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cryptocb.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/curve25519.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dh.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dsa.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc_fp.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ed25519.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/error.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_low_mem.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_operations.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_low_mem.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_operations.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hash.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hc128.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hmac.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/idea.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/integer.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/logging.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md2.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md4.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/memory.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs12.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs7.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/poly1305.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pwdbased.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rabbit.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ripemd.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rsa.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha3.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/signature.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm32.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm64.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_armthumb.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c32.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c64.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_cortexm.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_int.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_x86_64.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/srp.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/tfm.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_encrypt.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_pkcs11.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_port.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfevent.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfmath.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/aes.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/des3.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md5.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/random.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha256.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha512.c ../src/app.c ../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1664057780/misc.o ${OBJECTDIR}/_ext/978308758/bsp.o ${OBJECTDIR}/_ext/1997391349/crypto.o ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o ${OBJECTDIR}/_ext/138020607/drv_ethphy.o ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o ${OBJECTDIR}/_ext/1520632/drv_memory.o ${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o ${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o ${OBJECTDIR}/_ext/1761147401/drv_miim.o ${OBJECTDIR}/_ext/584638298/sys_fs_shell.o ${OBJECTDIR}/_ext/2027382860/helpers.o ${OBJECTDIR}/_ext/2027382860/dns.o ${OBJECTDIR}/_ext/2027382860/icmp.o ${OBJECTDIR}/_ext/2027382860/nbns.o ${OBJECTDIR}/_ext/2027382860/tcp.o ${OBJECTDIR}/_ext/2027382860/dhcp.o ${OBJECTDIR}/_ext/2027382860/arp.o ${OBJECTDIR}/_ext/2027382860/icmpv6.o ${OBJECTDIR}/_ext/2027382860/ndp.o ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o ${OBJECTDIR}/_ext/2027382860/ipv6.o ${OBJECTDIR}/_ext/2027382860/http.o ${OBJECTDIR}/_ext/2027382860/ipv4.o ${OBJECTDIR}/_ext/2027382860/smtpc.o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o ${OBJECTDIR}/_ext/2027382860/hash_fnv.o ${OBJECTDIR}/_ext/2027382860/oahash.o ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o ${OBJECTDIR}/_ext/2027382860/sntp.o ${OBJECTDIR}/_ext/2027382860/tcpip_announce.o ${OBJECTDIR}/_ext/2027382860/udp.o ${OBJECTDIR}/_ext/513706829/net_pres.o ${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o ${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o ${OBJECTDIR}/_ext/1098417660/plib_clk.o ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o ${OBJECTDIR}/_ext/308860137/plib_evic.o ${OBJECTDIR}/_ext/308913965/plib_gpio.o ${OBJECTDIR}/_ext/1098406777/plib_nvm.o ${OBJECTDIR}/_ext/309316908/plib_uart2.o ${OBJECTDIR}/_ext/458842868/xc32_monitor.o ${OBJECTDIR}/_ext/2135388491/sys_command.o ${OBJECTDIR}/_ext/1702866625/sys_console.o ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o ${OBJECTDIR}/_ext/57023747/sys_debug.o ${OBJECTDIR}/_ext/641613919/ff.o ${OBJECTDIR}/_ext/641613919/diskio.o ${OBJECTDIR}/_ext/883137948/mpfs.o ${OBJECTDIR}/_ext/1879727853/sys_fs.o ${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o ${OBJECTDIR}/_ext/723085273/sys_int.o ${OBJECTDIR}/_ext/1658225107/sys_time.o ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o ${OBJECTDIR}/_ext/942849350/tasks.o ${OBJECTDIR}/_ext/942849350/initialization.o ${OBJECTDIR}/_ext/942849350/interrupts.o ${OBJECTDIR}/_ext/942849350/exceptions.o ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o ${OBJECTDIR}/_ext/1360937237/modbus_app.o ${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o ${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o ${OBJECTDIR}/_ext/1360937237/d_eeprom.o ${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ${OBJECTDIR}/_ext/1360937237/http_print.o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ${OBJECTDIR}/_ext/1360937237/http_app.o ${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o ${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o ${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o ${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o ${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o ${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o ${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o ${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o ${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o ${OBJECTDIR}/_ext/1664057780/arc4.o ${OBJECTDIR}/_ext/1664057780/asm.o ${OBJECTDIR}/_ext/1664057780/asn.o ${OBJECTDIR}/_ext/1664057780/blake2b.o ${OBJECTDIR}/_ext/1664057780/blake2s.o ${OBJECTDIR}/_ext/1664057780/camellia.o ${OBJECTDIR}/_ext/1664057780/chacha.o ${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o ${OBJECTDIR}/_ext/1664057780/cmac.o ${OBJECTDIR}/_ext/1664057780/coding.o ${OBJECTDIR}/_ext/1664057780/compress.o ${OBJECTDIR}/_ext/1664057780/cpuid.o ${OBJECTDIR}/_ext/1664057780/cryptocb.o ${OBJECTDIR}/_ext/1664057780/curve25519.o ${OBJECTDIR}/_ext/1664057780/dh.o ${OBJECTDIR}/_ext/1664057780/dsa.o ${OBJECTDIR}/_ext/1664057780/ecc.o ${OBJECTDIR}/_ext/1664057780/ecc_fp.o ${OBJECTDIR}/_ext/1664057780/ed25519.o ${OBJECTDIR}/_ext/1664057780/error.o ${OBJECTDIR}/_ext/1664057780/fe_low_mem.o ${OBJECTDIR}/_ext/1664057780/fe_operations.o ${OBJECTDIR}/_ext/1664057780/ge_low_mem.o ${OBJECTDIR}/_ext/1664057780/ge_operations.o ${OBJECTDIR}/_ext/1664057780/hash.o ${OBJECTDIR}/_ext/1664057780/hc128.o ${OBJECTDIR}/_ext/1664057780/hmac.o ${OBJECTDIR}/_ext/1664057780/idea.o ${OBJECTDIR}/_ext/1664057780/integer.o ${OBJECTDIR}/_ext/1664057780/logging.o ${OBJECTDIR}/_ext/1664057780/md2.o ${OBJECTDIR}/_ext/1664057780/md4.o ${OBJECTDIR}/_ext/1664057780/memory.o ${OBJECTDIR}/_ext/1664057780/pkcs12.o ${OBJECTDIR}/_ext/1664057780/pkcs7.o ${OBJECTDIR}/_ext/1664057780/poly1305.o ${OBJECTDIR}/_ext/1664057780/pwdbased.o ${OBJECTDIR}/_ext/1664057780/rabbit.o ${OBJECTDIR}/_ext/1664057780/ripemd.o ${OBJECTDIR}/_ext/1664057780/rsa.o ${OBJECTDIR}/_ext/1664057780/sha3.o ${OBJECTDIR}/_ext/1664057780/signature.o ${OBJECTDIR}/_ext/1664057780/sp_arm32.o ${OBJECTDIR}/_ext/1664057780/sp_arm64.o ${OBJECTDIR}/_ext/1664057780/sp_armthumb.o ${OBJECTDIR}/_ext/1664057780/sp_c32.o ${OBJECTDIR}/_ext/1664057780/sp_c64.o ${OBJECTDIR}/_ext/1664057780/sp_cortexm.o ${OBJECTDIR}/_ext/1664057780/sp_int.o ${OBJECTDIR}/_ext/1664057780/sp_x86_64.o ${OBJECTDIR}/_ext/1664057780/srp.o ${OBJECTDIR}/_ext/1664057780/tfm.o ${OBJECTDIR}/_ext/1664057780/wc_encrypt.o ${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o ${OBJECTDIR}/_ext/1664057780/wc_port.o ${OBJECTDIR}/_ext/1664057780/wolfevent.o ${OBJECTDIR}/_ext/1664057780/wolfmath.o ${OBJECTDIR}/_ext/1664057780/aes.o ${OBJECTDIR}/_ext/1664057780/des3.o ${OBJECTDIR}/_ext/1664057780/md5.o ${OBJECTDIR}/_ext/1664057780/random.o ${OBJECTDIR}/_ext/1664057780/sha.o ${OBJECTDIR}/_ext/1664057780/sha256.o ${OBJECTDIR}/_ext/1664057780/sha512.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1664057780/misc.o.d ${OBJECTDIR}/_ext/978308758/bsp.o.d ${OBJECTDIR}/_ext/1997391349/crypto.o.d ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d ${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d ${OBJECTDIR}/_ext/1520632/drv_memory.o.d ${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o.d ${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o.d ${OBJECTDIR}/_ext/1761147401/drv_miim.o.d ${OBJECTDIR}/_ext/584638298/sys_fs_shell.o.d ${OBJECTDIR}/_ext/2027382860/helpers.o.d ${OBJECTDIR}/_ext/2027382860/dns.o.d ${OBJECTDIR}/_ext/2027382860/icmp.o.d ${OBJECTDIR}/_ext/2027382860/nbns.o.d ${OBJECTDIR}/_ext/2027382860/tcp.o.d ${OBJECTDIR}/_ext/2027382860/dhcp.o.d ${OBJECTDIR}/_ext/2027382860/arp.o.d ${OBJECTDIR}/_ext/2027382860/icmpv6.o.d ${OBJECTDIR}/_ext/2027382860/ndp.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d ${OBJECTDIR}/_ext/2027382860/ipv6.o.d ${OBJECTDIR}/_ext/2027382860/http.o.d ${OBJECTDIR}/_ext/2027382860/ipv4.o.d ${OBJECTDIR}/_ext/2027382860/smtpc.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d ${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d ${OBJECTDIR}/_ext/2027382860/oahash.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d ${OBJECTDIR}/_ext/2027382860/sntp.o.d ${OBJECTDIR}/_ext/2027382860/tcpip_announce.o.d ${OBJECTDIR}/_ext/2027382860/udp.o.d ${OBJECTDIR}/_ext/513706829/net_pres.o.d ${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o.d ${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o.d ${OBJECTDIR}/_ext/1098417660/plib_clk.o.d ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d ${OBJECTDIR}/_ext/308860137/plib_evic.o.d ${OBJECTDIR}/_ext/308913965/plib_gpio.o.d ${OBJECTDIR}/_ext/1098406777/plib_nvm.o.d ${OBJECTDIR}/_ext/309316908/plib_uart2.o.d ${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d ${OBJECTDIR}/_ext/2135388491/sys_command.o.d ${OBJECTDIR}/_ext/1702866625/sys_console.o.d ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d ${OBJECTDIR}/_ext/57023747/sys_debug.o.d ${OBJECTDIR}/_ext/641613919/ff.o.d ${OBJECTDIR}/_ext/641613919/diskio.o.d ${OBJECTDIR}/_ext/883137948/mpfs.o.d ${OBJECTDIR}/_ext/1879727853/sys_fs.o.d ${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o.d ${OBJECTDIR}/_ext/723085273/sys_int.o.d ${OBJECTDIR}/_ext/1658225107/sys_time.o.d ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d ${OBJECTDIR}/_ext/942849350/tasks.o.d ${OBJECTDIR}/_ext/942849350/initialization.o.d ${OBJECTDIR}/_ext/942849350/interrupts.o.d ${OBJECTDIR}/_ext/942849350/exceptions.o.d ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d ${OBJECTDIR}/_ext/1360937237/modbus_app.o.d ${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o.d ${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o.d ${OBJECTDIR}/_ext/1360937237/d_eeprom.o.d ${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o.d ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d ${OBJECTDIR}/_ext/1360937237/http_print.o.d ${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d ${OBJECTDIR}/_ext/1360937237/http_app.o.d ${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o.d ${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o.d ${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o.d ${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o.d ${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o.d ${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o.d ${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o.d ${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o.d ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o.d ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o.d ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o.d ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o.d ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o.d ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o.d ${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o.d ${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o.d ${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o.d ${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o.d ${OBJECTDIR}/_ext/1664057780/arc4.o.d ${OBJECTDIR}/_ext/1664057780/asm.o.d ${OBJECTDIR}/_ext/1664057780/asn.o.d ${OBJECTDIR}/_ext/1664057780/blake2b.o.d ${OBJECTDIR}/_ext/1664057780/blake2s.o.d ${OBJECTDIR}/_ext/1664057780/camellia.o.d ${OBJECTDIR}/_ext/1664057780/chacha.o.d ${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o.d ${OBJECTDIR}/_ext/1664057780/cmac.o.d ${OBJECTDIR}/_ext/1664057780/coding.o.d ${OBJECTDIR}/_ext/1664057780/compress.o.d ${OBJECTDIR}/_ext/1664057780/cpuid.o.d ${OBJECTDIR}/_ext/1664057780/cryptocb.o.d ${OBJECTDIR}/_ext/1664057780/curve25519.o.d ${OBJECTDIR}/_ext/1664057780/dh.o.d ${OBJECTDIR}/_ext/1664057780/dsa.o.d ${OBJECTDIR}/_ext/1664057780/ecc.o.d ${OBJECTDIR}/_ext/1664057780/ecc_fp.o.d ${OBJECTDIR}/_ext/1664057780/ed25519.o.d ${OBJECTDIR}/_ext/1664057780/error.o.d ${OBJECTDIR}/_ext/1664057780/fe_low_mem.o.d ${OBJECTDIR}/_ext/1664057780/fe_operations.o.d ${OBJECTDIR}/_ext/1664057780/ge_low_mem.o.d ${OBJECTDIR}/_ext/1664057780/ge_operations.o.d ${OBJECTDIR}/_ext/1664057780/hash.o.d ${OBJECTDIR}/_ext/1664057780/hc128.o.d ${OBJECTDIR}/_ext/1664057780/hmac.o.d ${OBJECTDIR}/_ext/1664057780/idea.o.d ${OBJECTDIR}/_ext/1664057780/integer.o.d ${OBJECTDIR}/_ext/1664057780/logging.o.d ${OBJECTDIR}/_ext/1664057780/md2.o.d ${OBJECTDIR}/_ext/1664057780/md4.o.d ${OBJECTDIR}/_ext/1664057780/memory.o.d ${OBJECTDIR}/_ext/1664057780/pkcs12.o.d ${OBJECTDIR}/_ext/1664057780/pkcs7.o.d ${OBJECTDIR}/_ext/1664057780/poly1305.o.d ${OBJECTDIR}/_ext/1664057780/pwdbased.o.d ${OBJECTDIR}/_ext/1664057780/rabbit.o.d ${OBJECTDIR}/_ext/1664057780/ripemd.o.d ${OBJECTDIR}/_ext/1664057780/rsa.o.d ${OBJECTDIR}/_ext/1664057780/sha3.o.d ${OBJECTDIR}/_ext/1664057780/signature.o.d ${OBJECTDIR}/_ext/1664057780/sp_arm32.o.d ${OBJECTDIR}/_ext/1664057780/sp_arm64.o.d ${OBJECTDIR}/_ext/1664057780/sp_armthumb.o.d ${OBJECTDIR}/_ext/1664057780/sp_c32.o.d ${OBJECTDIR}/_ext/1664057780/sp_c64.o.d ${OBJECTDIR}/_ext/1664057780/sp_cortexm.o.d ${OBJECTDIR}/_ext/1664057780/sp_int.o.d ${OBJECTDIR}/_ext/1664057780/sp_x86_64.o.d ${OBJECTDIR}/_ext/1664057780/srp.o.d ${OBJECTDIR}/_ext/1664057780/tfm.o.d ${OBJECTDIR}/_ext/1664057780/wc_encrypt.o.d ${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o.d ${OBJECTDIR}/_ext/1664057780/wc_port.o.d ${OBJECTDIR}/_ext/1664057780/wolfevent.o.d ${OBJECTDIR}/_ext/1664057780/wolfmath.o.d ${OBJECTDIR}/_ext/1664057780/aes.o.d ${OBJECTDIR}/_ext/1664057780/des3.o.d ${OBJECTDIR}/_ext/1664057780/md5.o.d ${OBJECTDIR}/_ext/1664057780/random.o.d ${OBJECTDIR}/_ext/1664057780/sha.o.d ${OBJECTDIR}/_ext/1664057780/sha256.o.d ${OBJECTDIR}/_ext/1664057780/sha512.o.d ${OBJECTDIR}/_ext/1360937237/app.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1664057780/misc.o ${OBJECTDIR}/_ext/978308758/bsp.o ${OBJECTDIR}/_ext/1997391349/crypto.o ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o ${OBJECTDIR}/_ext/138020607/drv_ethphy.o ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o ${OBJECTDIR}/_ext/1520632/drv_memory.o ${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o ${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o ${OBJECTDIR}/_ext/1761147401/drv_miim.o ${OBJECTDIR}/_ext/584638298/sys_fs_shell.o ${OBJECTDIR}/_ext/2027382860/helpers.o ${OBJECTDIR}/_ext/2027382860/dns.o ${OBJECTDIR}/_ext/2027382860/icmp.o ${OBJECTDIR}/_ext/2027382860/nbns.o ${OBJECTDIR}/_ext/2027382860/tcp.o ${OBJECTDIR}/_ext/2027382860/dhcp.o ${OBJECTDIR}/_ext/2027382860/arp.o ${OBJECTDIR}/_ext/2027382860/icmpv6.o ${OBJECTDIR}/_ext/2027382860/ndp.o ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o ${OBJECTDIR}/_ext/2027382860/ipv6.o ${OBJECTDIR}/_ext/2027382860/http.o ${OBJECTDIR}/_ext/2027382860/ipv4.o ${OBJECTDIR}/_ext/2027382860/smtpc.o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o ${OBJECTDIR}/_ext/2027382860/hash_fnv.o ${OBJECTDIR}/_ext/2027382860/oahash.o ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o ${OBJECTDIR}/_ext/2027382860/sntp.o ${OBJECTDIR}/_ext/2027382860/tcpip_announce.o ${OBJECTDIR}/_ext/2027382860/udp.o ${OBJECTDIR}/_ext/513706829/net_pres.o ${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o ${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o ${OBJECTDIR}/_ext/1098417660/plib_clk.o ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o ${OBJECTDIR}/_ext/308860137/plib_evic.o ${OBJECTDIR}/_ext/308913965/plib_gpio.o ${OBJECTDIR}/_ext/1098406777/plib_nvm.o ${OBJECTDIR}/_ext/309316908/plib_uart2.o ${OBJECTDIR}/_ext/458842868/xc32_monitor.o ${OBJECTDIR}/_ext/2135388491/sys_command.o ${OBJECTDIR}/_ext/1702866625/sys_console.o ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o ${OBJECTDIR}/_ext/57023747/sys_debug.o ${OBJECTDIR}/_ext/641613919/ff.o ${OBJECTDIR}/_ext/641613919/diskio.o ${OBJECTDIR}/_ext/883137948/mpfs.o ${OBJECTDIR}/_ext/1879727853/sys_fs.o ${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o ${OBJECTDIR}/_ext/723085273/sys_int.o ${OBJECTDIR}/_ext/1658225107/sys_time.o ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o ${OBJECTDIR}/_ext/942849350/tasks.o ${OBJECTDIR}/_ext/942849350/initialization.o ${OBJECTDIR}/_ext/942849350/interrupts.o ${OBJECTDIR}/_ext/942849350/exceptions.o ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o ${OBJECTDIR}/_ext/1360937237/modbus_app.o ${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o ${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o ${OBJECTDIR}/_ext/1360937237/d_eeprom.o ${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ${OBJECTDIR}/_ext/1360937237/http_print.o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ${OBJECTDIR}/_ext/1360937237/http_app.o ${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o ${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o ${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o ${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o ${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o ${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o ${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o ${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o ${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o ${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o ${OBJECTDIR}/_ext/1664057780/arc4.o ${OBJECTDIR}/_ext/1664057780/asm.o ${OBJECTDIR}/_ext/1664057780/asn.o ${OBJECTDIR}/_ext/1664057780/blake2b.o ${OBJECTDIR}/_ext/1664057780/blake2s.o ${OBJECTDIR}/_ext/1664057780/camellia.o ${OBJECTDIR}/_ext/1664057780/chacha.o ${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o ${OBJECTDIR}/_ext/1664057780/cmac.o ${OBJECTDIR}/_ext/1664057780/coding.o ${OBJECTDIR}/_ext/1664057780/compress.o ${OBJECTDIR}/_ext/1664057780/cpuid.o ${OBJECTDIR}/_ext/1664057780/cryptocb.o ${OBJECTDIR}/_ext/1664057780/curve25519.o ${OBJECTDIR}/_ext/1664057780/dh.o ${OBJECTDIR}/_ext/1664057780/dsa.o ${OBJECTDIR}/_ext/1664057780/ecc.o ${OBJECTDIR}/_ext/1664057780/ecc_fp.o ${OBJECTDIR}/_ext/1664057780/ed25519.o ${OBJECTDIR}/_ext/1664057780/error.o ${OBJECTDIR}/_ext/1664057780/fe_low_mem.o ${OBJECTDIR}/_ext/1664057780/fe_operations.o ${OBJECTDIR}/_ext/1664057780/ge_low_mem.o ${OBJECTDIR}/_ext/1664057780/ge_operations.o ${OBJECTDIR}/_ext/1664057780/hash.o ${OBJECTDIR}/_ext/1664057780/hc128.o ${OBJECTDIR}/_ext/1664057780/hmac.o ${OBJECTDIR}/_ext/1664057780/idea.o ${OBJECTDIR}/_ext/1664057780/integer.o ${OBJECTDIR}/_ext/1664057780/logging.o ${OBJECTDIR}/_ext/1664057780/md2.o ${OBJECTDIR}/_ext/1664057780/md4.o ${OBJECTDIR}/_ext/1664057780/memory.o ${OBJECTDIR}/_ext/1664057780/pkcs12.o ${OBJECTDIR}/_ext/1664057780/pkcs7.o ${OBJECTDIR}/_ext/1664057780/poly1305.o ${OBJECTDIR}/_ext/1664057780/pwdbased.o ${OBJECTDIR}/_ext/1664057780/rabbit.o ${OBJECTDIR}/_ext/1664057780/ripemd.o ${OBJECTDIR}/_ext/1664057780/rsa.o ${OBJECTDIR}/_ext/1664057780/sha3.o ${OBJECTDIR}/_ext/1664057780/signature.o ${OBJECTDIR}/_ext/1664057780/sp_arm32.o ${OBJECTDIR}/_ext/1664057780/sp_arm64.o ${OBJECTDIR}/_ext/1664057780/sp_armthumb.o ${OBJECTDIR}/_ext/1664057780/sp_c32.o ${OBJECTDIR}/_ext/1664057780/sp_c64.o ${OBJECTDIR}/_ext/1664057780/sp_cortexm.o ${OBJECTDIR}/_ext/1664057780/sp_int.o ${OBJECTDIR}/_ext/1664057780/sp_x86_64.o ${OBJECTDIR}/_ext/1664057780/srp.o ${OBJECTDIR}/_ext/1664057780/tfm.o ${OBJECTDIR}/_ext/1664057780/wc_encrypt.o ${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o ${OBJECTDIR}/_ext/1664057780/wc_port.o ${OBJECTDIR}/_ext/1664057780/wolfevent.o ${OBJECTDIR}/_ext/1664057780/wolfmath.o ${OBJECTDIR}/_ext/1664057780/aes.o ${OBJECTDIR}/_ext/1664057780/des3.o ${OBJECTDIR}/_ext/1664057780/md5.o ${OBJECTDIR}/_ext/1664057780/random.o ${OBJECTDIR}/_ext/1664057780/sha.o ${OBJECTDIR}/_ext/1664057780/sha256.o ${OBJECTDIR}/_ext/1664057780/sha512.o ${OBJECTDIR}/_ext/1360937237/app.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../src/third_party/wolfssl/wolfssl/wolfcrypt/src/misc.c ../src/config/pic32mz_ef_sk/bsp/bsp.c ../src/config/pic32mz_ef_sk/crypto/src/crypto.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory.c ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_file_system.c ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_nvm.c ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c ../src/config/pic32mz_ef_sk/library/tcpip/src/common/sys_fs_shell.c ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/nbns.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/icmpv6.c ../src/config/pic32mz_ef_sk/library/tcpip/src/ndp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv6.c ../src/config/pic32mz_ef_sk/library/tcpip/src/http.c ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c ../src/config/pic32mz_ef_sk/library/tcpip/src/smtpc.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c ../src/config/pic32mz_ef_sk/library/tcpip/src/sntp.c ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_announce.c ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c ../src/config/pic32mz_ef_sk/net_pres/pres/src/net_pres.c ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_enc_glue.c ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_cert_store.c ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c ../src/config/pic32mz_ef_sk/peripheral/nvm/plib_nvm.c ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/ff.c ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/diskio.c ../src/config/pic32mz_ef_sk/system/fs/mpfs/src/mpfs.c ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs.c ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs_media_manager.c ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c ../src/config/pic32mz_ef_sk/tasks.c ../src/config/pic32mz_ef_sk/initialization.c ../src/config/pic32mz_ef_sk/interrupts.c ../src/config/pic32mz_ef_sk/exceptions.c ../src/modbus/dialtek_modbus.c ../src/modbus_app.c ../src/modbus_buf_tcp.c ../src/PIC32MZ_SPI.c ../src/d_eeprom.c ../src/PIC32MZ_UART.c ../src/mpfs_img2.c ../src/http_print.c ../src/custom_http_app.c ../src/http_app.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/pic32mz-crypt.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_sam6149.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_u2238.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_ecc_pukcl.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_pukcl_functions.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_sam6334.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_u2242.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rsa_pukcl.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam11105.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam11105.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam11105.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha384_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha512_sam6156.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_tdes_sam6150.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_wolfcryptcb.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/arc4.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asm.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asn.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2b.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2s.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/camellia.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha20_poly1305.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cmac.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/coding.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/compress.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cpuid.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cryptocb.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/curve25519.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dh.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dsa.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc_fp.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ed25519.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/error.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_low_mem.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_operations.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_low_mem.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_operations.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hash.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hc128.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hmac.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/idea.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/integer.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/logging.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md2.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md4.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/memory.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs12.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs7.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/poly1305.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pwdbased.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rabbit.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ripemd.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rsa.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha3.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/signature.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm32.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm64.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_armthumb.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c32.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c64.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_cortexm.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_int.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_x86_64.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/srp.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/tfm.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_encrypt.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_pkcs11.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_port.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfevent.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfmath.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/aes.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/des3.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md5.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/random.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha256.c ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha512.c ../src/app.c ../src/main.c



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
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d" "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1 -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S  -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD4=1 -mdfp=${DFP_DIR}
	
else
${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.ok ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.err 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d" "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.d"  -o ${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helper_c32.S  -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/_ext/2027382860/tcpip_helper_c32.o.asm.d",--gdwarf-2 -mdfp=${DFP_DIR}
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1664057780/misc.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/misc.o.d" -o ${OBJECTDIR}/_ext/1664057780/misc.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/misc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/978308758/bsp.o: ../src/config/pic32mz_ef_sk/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/978308758" 
	@${RM} ${OBJECTDIR}/_ext/978308758/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/978308758/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/978308758/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/978308758/bsp.o.d" -o ${OBJECTDIR}/_ext/978308758/bsp.o ../src/config/pic32mz_ef_sk/bsp/bsp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1997391349/crypto.o: ../src/config/pic32mz_ef_sk/crypto/src/crypto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1997391349" 
	@${RM} ${OBJECTDIR}/_ext/1997391349/crypto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1997391349/crypto.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1997391349/crypto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1997391349/crypto.o.d" -o ${OBJECTDIR}/_ext/1997391349/crypto.o ../src/config/pic32mz_ef_sk/crypto/src/crypto.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1314174413/drv_ethmac.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/138020607/drv_ethphy.o: ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/138020607" 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_ethphy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d" -o ${OBJECTDIR}/_ext/138020607/drv_ethphy.o ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o: ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/138020607" 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d" -o ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1520632/drv_memory.o: ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1520632" 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1520632/drv_memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1520632/drv_memory.o.d" -o ${OBJECTDIR}/_ext/1520632/drv_memory.o ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o: ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_file_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1520632" 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o.d" -o ${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_file_system.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o: ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1520632" 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o.d" -o ${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_nvm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1761147401/drv_miim.o: ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1761147401" 
	@${RM} ${OBJECTDIR}/_ext/1761147401/drv_miim.o.d 
	@${RM} ${OBJECTDIR}/_ext/1761147401/drv_miim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1761147401/drv_miim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1761147401/drv_miim.o.d" -o ${OBJECTDIR}/_ext/1761147401/drv_miim.o ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/584638298/sys_fs_shell.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/common/sys_fs_shell.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/584638298" 
	@${RM} ${OBJECTDIR}/_ext/584638298/sys_fs_shell.o.d 
	@${RM} ${OBJECTDIR}/_ext/584638298/sys_fs_shell.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/584638298/sys_fs_shell.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/584638298/sys_fs_shell.o.d" -o ${OBJECTDIR}/_ext/584638298/sys_fs_shell.o ../src/config/pic32mz_ef_sk/library/tcpip/src/common/sys_fs_shell.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/helpers.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/helpers.o.d" -o ${OBJECTDIR}/_ext/2027382860/helpers.o ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/dns.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/dns.o.d" -o ${OBJECTDIR}/_ext/2027382860/dns.o ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/icmp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/icmp.o.d" -o ${OBJECTDIR}/_ext/2027382860/icmp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/nbns.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/nbns.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/nbns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/nbns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/nbns.o.d" -o ${OBJECTDIR}/_ext/2027382860/nbns.o ../src/config/pic32mz_ef_sk/library/tcpip/src/nbns.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcp.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/dhcp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dhcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dhcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/dhcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/dhcp.o.d" -o ${OBJECTDIR}/_ext/2027382860/dhcp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/arp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/arp.o.d" -o ${OBJECTDIR}/_ext/2027382860/arp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/icmpv6.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/icmpv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmpv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmpv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/icmpv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/icmpv6.o.d" -o ${OBJECTDIR}/_ext/2027382860/icmpv6.o ../src/config/pic32mz_ef_sk/library/tcpip/src/icmpv6.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/ndp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/ndp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ndp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ndp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/ndp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/ndp.o.d" -o ${OBJECTDIR}/_ext/2027382860/ndp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/ndp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_commands.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/ipv6.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/ipv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/ipv6.o.d" -o ${OBJECTDIR}/_ext/2027382860/ipv6.o ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv6.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/http.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/http.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/http.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/http.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/http.o.d" -o ${OBJECTDIR}/_ext/2027382860/http.o ../src/config/pic32mz_ef_sk/library/tcpip/src/http.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/ipv4.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/ipv4.o.d" -o ${OBJECTDIR}/_ext/2027382860/ipv4.o ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/smtpc.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/smtpc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/smtpc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/smtpc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/smtpc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/smtpc.o.d" -o ${OBJECTDIR}/_ext/2027382860/smtpc.o ../src/config/pic32mz_ef_sk/library/tcpip/src/smtpc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/hash_fnv.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/hash_fnv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d" -o ${OBJECTDIR}/_ext/2027382860/hash_fnv.o ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/oahash.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/oahash.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/oahash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/oahash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/oahash.o.d" -o ${OBJECTDIR}/_ext/2027382860/oahash.o ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_manager.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_notify.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_packet.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/sntp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/sntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/sntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/sntp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/sntp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/sntp.o.d" -o ${OBJECTDIR}/_ext/2027382860/sntp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/sntp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_announce.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_announce.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_announce.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_announce.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/udp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/udp.o.d" -o ${OBJECTDIR}/_ext/2027382860/udp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/513706829/net_pres.o: ../src/config/pic32mz_ef_sk/net_pres/pres/src/net_pres.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513706829" 
	@${RM} ${OBJECTDIR}/_ext/513706829/net_pres.o.d 
	@${RM} ${OBJECTDIR}/_ext/513706829/net_pres.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513706829/net_pres.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/513706829/net_pres.o.d" -o ${OBJECTDIR}/_ext/513706829/net_pres.o ../src/config/pic32mz_ef_sk/net_pres/pres/src/net_pres.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o: ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_enc_glue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1508781048" 
	@${RM} ${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o.d" -o ${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_enc_glue.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o: ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_cert_store.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1508781048" 
	@${RM} ${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o.d 
	@${RM} ${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o.d" -o ${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_cert_store.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1098417660/plib_clk.o: ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1098417660" 
	@${RM} ${OBJECTDIR}/_ext/1098417660/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1098417660/plib_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1098417660/plib_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1098417660/plib_clk.o.d" -o ${OBJECTDIR}/_ext/1098417660/plib_clk.o ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1710852712/plib_coretimer.o: ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1710852712" 
	@${RM} ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/308860137/plib_evic.o: ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/308860137" 
	@${RM} ${OBJECTDIR}/_ext/308860137/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/308860137/plib_evic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/308860137/plib_evic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/308860137/plib_evic.o.d" -o ${OBJECTDIR}/_ext/308860137/plib_evic.o ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/308913965/plib_gpio.o: ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/308913965" 
	@${RM} ${OBJECTDIR}/_ext/308913965/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/308913965/plib_gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/308913965/plib_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/308913965/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/308913965/plib_gpio.o ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1098406777/plib_nvm.o: ../src/config/pic32mz_ef_sk/peripheral/nvm/plib_nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1098406777" 
	@${RM} ${OBJECTDIR}/_ext/1098406777/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1098406777/plib_nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1098406777/plib_nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1098406777/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/1098406777/plib_nvm.o ../src/config/pic32mz_ef_sk/peripheral/nvm/plib_nvm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/309316908/plib_uart2.o: ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/309316908" 
	@${RM} ${OBJECTDIR}/_ext/309316908/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/309316908/plib_uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/309316908/plib_uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/309316908/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/309316908/plib_uart2.o ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/458842868/xc32_monitor.o: ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/458842868" 
	@${RM} ${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/458842868/xc32_monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/458842868/xc32_monitor.o ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2135388491/sys_command.o: ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2135388491" 
	@${RM} ${OBJECTDIR}/_ext/2135388491/sys_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/2135388491/sys_command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2135388491/sys_command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2135388491/sys_command.o.d" -o ${OBJECTDIR}/_ext/2135388491/sys_command.o ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1702866625/sys_console.o: ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1702866625" 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1702866625/sys_console.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1702866625/sys_console.o.d" -o ${OBJECTDIR}/_ext/1702866625/sys_console.o ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1702866625/sys_console_uart.o: ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1702866625" 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/57023747/sys_debug.o: ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/57023747" 
	@${RM} ${OBJECTDIR}/_ext/57023747/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/57023747/sys_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/57023747/sys_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/57023747/sys_debug.o.d" -o ${OBJECTDIR}/_ext/57023747/sys_debug.o ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/641613919/ff.o: ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/641613919" 
	@${RM} ${OBJECTDIR}/_ext/641613919/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/641613919/ff.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/641613919/ff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/641613919/ff.o.d" -o ${OBJECTDIR}/_ext/641613919/ff.o ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/ff.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/641613919/diskio.o: ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/diskio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/641613919" 
	@${RM} ${OBJECTDIR}/_ext/641613919/diskio.o.d 
	@${RM} ${OBJECTDIR}/_ext/641613919/diskio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/641613919/diskio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/641613919/diskio.o.d" -o ${OBJECTDIR}/_ext/641613919/diskio.o ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/diskio.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/883137948/mpfs.o: ../src/config/pic32mz_ef_sk/system/fs/mpfs/src/mpfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/883137948" 
	@${RM} ${OBJECTDIR}/_ext/883137948/mpfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/883137948/mpfs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/883137948/mpfs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/883137948/mpfs.o.d" -o ${OBJECTDIR}/_ext/883137948/mpfs.o ../src/config/pic32mz_ef_sk/system/fs/mpfs/src/mpfs.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1879727853/sys_fs.o: ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1879727853" 
	@${RM} ${OBJECTDIR}/_ext/1879727853/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1879727853/sys_fs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1879727853/sys_fs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1879727853/sys_fs.o.d" -o ${OBJECTDIR}/_ext/1879727853/sys_fs.o ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o: ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs_media_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1879727853" 
	@${RM} ${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o.d" -o ${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs_media_manager.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/723085273/sys_int.o: ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/723085273" 
	@${RM} ${OBJECTDIR}/_ext/723085273/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/723085273/sys_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/723085273/sys_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/723085273/sys_int.o.d" -o ${OBJECTDIR}/_ext/723085273/sys_int.o ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1658225107/sys_time.o: ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1658225107" 
	@${RM} ${OBJECTDIR}/_ext/1658225107/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1658225107/sys_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1658225107/sys_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1658225107/sys_time.o.d" -o ${OBJECTDIR}/_ext/1658225107/sys_time.o ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o: ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344301860" 
	@${RM} ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d" -o ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/942849350/tasks.o: ../src/config/pic32mz_ef_sk/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/942849350/tasks.o.d" -o ${OBJECTDIR}/_ext/942849350/tasks.o ../src/config/pic32mz_ef_sk/tasks.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/942849350/initialization.o: ../src/config/pic32mz_ef_sk/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/initialization.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/942849350/initialization.o.d" -o ${OBJECTDIR}/_ext/942849350/initialization.o ../src/config/pic32mz_ef_sk/initialization.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/942849350/interrupts.o: ../src/config/pic32mz_ef_sk/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/942849350/interrupts.o.d" -o ${OBJECTDIR}/_ext/942849350/interrupts.o ../src/config/pic32mz_ef_sk/interrupts.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/942849350/exceptions.o: ../src/config/pic32mz_ef_sk/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/942849350/exceptions.o.d" -o ${OBJECTDIR}/_ext/942849350/exceptions.o ../src/config/pic32mz_ef_sk/exceptions.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/108032392/dialtek_modbus.o: ../src/modbus/dialtek_modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/108032392" 
	@${RM} ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d 
	@${RM} ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d" -o ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o ../src/modbus/dialtek_modbus.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/modbus_app.o: ../src/modbus_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/modbus_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/modbus_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/modbus_app.o ../src/modbus_app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o: ../src/modbus_buf_tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o.d" -o ${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o ../src/modbus_buf_tcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o: ../src/PIC32MZ_SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o.d" -o ${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o ../src/PIC32MZ_SPI.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/d_eeprom.o: ../src/d_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/d_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/d_eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/d_eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/d_eeprom.o.d" -o ${OBJECTDIR}/_ext/1360937237/d_eeprom.o ../src/d_eeprom.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o: ../src/PIC32MZ_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o.d" -o ${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o ../src/PIC32MZ_UART.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/mpfs_img2.o: ../src/mpfs_img2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" -o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ../src/mpfs_img2.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/http_print.o: ../src/http_print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_print.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_print.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/http_print.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/http_print.o.d" -o ${OBJECTDIR}/_ext/1360937237/http_print.o ../src/http_print.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/custom_http_app.o: ../src/custom_http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ../src/custom_http_app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/http_app.o: ../src/http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/http_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/http_app.o ../src/http_app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/pic32mz-crypt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o.d" -o ${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/pic32mz-crypt.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_sam6149.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_sam6149.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_u2238.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_u2238.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_ecc_pukcl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_ecc_pukcl.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_pukcl_functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_pukcl_functions.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_sam6334.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_sam6334.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_u2242.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_u2242.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rsa_pukcl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rsa_pukcl.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam11105.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam11105.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam11105.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam11105.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam11105.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam11105.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha384_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha384_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha512_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha512_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_tdes_sam6150.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_tdes_sam6150.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_wolfcryptcb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_wolfcryptcb.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/arc4.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/arc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/arc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/arc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/arc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/arc4.o.d" -o ${OBJECTDIR}/_ext/1664057780/arc4.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/arc4.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/asm.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/asm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/asm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/asm.o.d" -o ${OBJECTDIR}/_ext/1664057780/asm.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/asn.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/asn.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/asn.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/asn.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/asn.o.d" -o ${OBJECTDIR}/_ext/1664057780/asn.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asn.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/blake2b.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2b.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/blake2b.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/blake2b.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/blake2b.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/blake2b.o.d" -o ${OBJECTDIR}/_ext/1664057780/blake2b.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2b.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/blake2s.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2s.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/blake2s.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/blake2s.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/blake2s.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/blake2s.o.d" -o ${OBJECTDIR}/_ext/1664057780/blake2s.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2s.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/camellia.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/camellia.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/camellia.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/camellia.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/camellia.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/camellia.o.d" -o ${OBJECTDIR}/_ext/1664057780/camellia.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/camellia.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/chacha.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/chacha.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/chacha.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/chacha.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/chacha.o.d" -o ${OBJECTDIR}/_ext/1664057780/chacha.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha20_poly1305.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o.d" -o ${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha20_poly1305.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/cmac.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/cmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/cmac.o.d" -o ${OBJECTDIR}/_ext/1664057780/cmac.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cmac.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/coding.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/coding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/coding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/coding.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/coding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/coding.o.d" -o ${OBJECTDIR}/_ext/1664057780/coding.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/coding.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/compress.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/compress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/compress.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/compress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/compress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/compress.o.d" -o ${OBJECTDIR}/_ext/1664057780/compress.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/compress.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/cpuid.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cpuid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cpuid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cpuid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/cpuid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/cpuid.o.d" -o ${OBJECTDIR}/_ext/1664057780/cpuid.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cpuid.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/cryptocb.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cryptocb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cryptocb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cryptocb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/cryptocb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/cryptocb.o.d" -o ${OBJECTDIR}/_ext/1664057780/cryptocb.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cryptocb.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/curve25519.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/curve25519.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/curve25519.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/curve25519.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/curve25519.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/curve25519.o.d" -o ${OBJECTDIR}/_ext/1664057780/curve25519.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/curve25519.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/dh.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dh.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/dh.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/dh.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/dh.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/dh.o.d" -o ${OBJECTDIR}/_ext/1664057780/dh.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dh.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/dsa.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/dsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/dsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/dsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/dsa.o.d" -o ${OBJECTDIR}/_ext/1664057780/dsa.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dsa.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ecc.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ecc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ecc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ecc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ecc.o.d" -o ${OBJECTDIR}/_ext/1664057780/ecc.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ecc_fp.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc_fp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ecc_fp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ecc_fp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ecc_fp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ecc_fp.o.d" -o ${OBJECTDIR}/_ext/1664057780/ecc_fp.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc_fp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ed25519.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ed25519.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ed25519.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ed25519.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ed25519.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ed25519.o.d" -o ${OBJECTDIR}/_ext/1664057780/ed25519.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ed25519.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/error.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/error.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/error.o.d" -o ${OBJECTDIR}/_ext/1664057780/error.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/error.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/fe_low_mem.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_low_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/fe_low_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/fe_low_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/fe_low_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/fe_low_mem.o.d" -o ${OBJECTDIR}/_ext/1664057780/fe_low_mem.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_low_mem.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/fe_operations.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_operations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/fe_operations.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/fe_operations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/fe_operations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/fe_operations.o.d" -o ${OBJECTDIR}/_ext/1664057780/fe_operations.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_operations.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ge_low_mem.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_low_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ge_low_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ge_low_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ge_low_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ge_low_mem.o.d" -o ${OBJECTDIR}/_ext/1664057780/ge_low_mem.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_low_mem.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ge_operations.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_operations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ge_operations.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ge_operations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ge_operations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ge_operations.o.d" -o ${OBJECTDIR}/_ext/1664057780/ge_operations.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_operations.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/hash.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/hash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/hash.o.d" -o ${OBJECTDIR}/_ext/1664057780/hash.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hash.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/hc128.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hc128.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hc128.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hc128.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/hc128.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/hc128.o.d" -o ${OBJECTDIR}/_ext/1664057780/hc128.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hc128.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/hmac.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/hmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/hmac.o.d" -o ${OBJECTDIR}/_ext/1664057780/hmac.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hmac.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/idea.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/idea.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/idea.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/idea.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/idea.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/idea.o.d" -o ${OBJECTDIR}/_ext/1664057780/idea.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/idea.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/integer.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/integer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/integer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/integer.o.d" -o ${OBJECTDIR}/_ext/1664057780/integer.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/integer.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/logging.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/logging.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/logging.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/logging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/logging.o.d" -o ${OBJECTDIR}/_ext/1664057780/logging.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/logging.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/md2.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/md2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/md2.o.d" -o ${OBJECTDIR}/_ext/1664057780/md2.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md2.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/md4.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/md4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/md4.o.d" -o ${OBJECTDIR}/_ext/1664057780/md4.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md4.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/memory.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/memory.o.d" -o ${OBJECTDIR}/_ext/1664057780/memory.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/memory.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/pkcs12.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pkcs12.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pkcs12.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/pkcs12.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/pkcs12.o.d" -o ${OBJECTDIR}/_ext/1664057780/pkcs12.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs12.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/pkcs7.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pkcs7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pkcs7.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/pkcs7.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/pkcs7.o.d" -o ${OBJECTDIR}/_ext/1664057780/pkcs7.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs7.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/poly1305.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/poly1305.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/poly1305.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/poly1305.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/poly1305.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/poly1305.o.d" -o ${OBJECTDIR}/_ext/1664057780/poly1305.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/poly1305.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/pwdbased.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pwdbased.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pwdbased.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pwdbased.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/pwdbased.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/pwdbased.o.d" -o ${OBJECTDIR}/_ext/1664057780/pwdbased.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pwdbased.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/rabbit.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rabbit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/rabbit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/rabbit.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/rabbit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/rabbit.o.d" -o ${OBJECTDIR}/_ext/1664057780/rabbit.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rabbit.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ripemd.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ripemd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ripemd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ripemd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ripemd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ripemd.o.d" -o ${OBJECTDIR}/_ext/1664057780/ripemd.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ripemd.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/rsa.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/rsa.o.d" -o ${OBJECTDIR}/_ext/1664057780/rsa.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rsa.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sha3.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sha3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sha3.o.d" -o ${OBJECTDIR}/_ext/1664057780/sha3.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha3.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/signature.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/signature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/signature.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/signature.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/signature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/signature.o.d" -o ${OBJECTDIR}/_ext/1664057780/signature.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/signature.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_arm32.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_arm32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_arm32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_arm32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_arm32.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_arm32.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm32.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_arm64.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_arm64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_arm64.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_arm64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_arm64.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_arm64.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm64.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_armthumb.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_armthumb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_armthumb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_armthumb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_armthumb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_armthumb.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_armthumb.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_armthumb.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_c32.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_c32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_c32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_c32.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_c32.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c32.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_c64.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_c64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_c64.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_c64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_c64.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_c64.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c64.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_cortexm.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_cortexm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_cortexm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_cortexm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_cortexm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_cortexm.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_cortexm.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_cortexm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_int.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_int.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_int.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_int.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_x86_64.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_x86_64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_x86_64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_x86_64.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_x86_64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_x86_64.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_x86_64.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_x86_64.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/srp.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/srp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/srp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/srp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/srp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/srp.o.d" -o ${OBJECTDIR}/_ext/1664057780/srp.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/srp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/tfm.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/tfm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/tfm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/tfm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/tfm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/tfm.o.d" -o ${OBJECTDIR}/_ext/1664057780/tfm.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/tfm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wc_encrypt.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_encrypt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_encrypt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_encrypt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wc_encrypt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wc_encrypt.o.d" -o ${OBJECTDIR}/_ext/1664057780/wc_encrypt.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_encrypt.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_pkcs11.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o.d" -o ${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_pkcs11.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wc_port.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wc_port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wc_port.o.d" -o ${OBJECTDIR}/_ext/1664057780/wc_port.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_port.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wolfevent.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfevent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wolfevent.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wolfevent.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wolfevent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wolfevent.o.d" -o ${OBJECTDIR}/_ext/1664057780/wolfevent.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfevent.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wolfmath.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfmath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wolfmath.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wolfmath.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wolfmath.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wolfmath.o.d" -o ${OBJECTDIR}/_ext/1664057780/wolfmath.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfmath.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/aes.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/aes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/aes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/aes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/aes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/aes.o.d" -o ${OBJECTDIR}/_ext/1664057780/aes.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/aes.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/des3.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/des3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/des3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/des3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/des3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/des3.o.d" -o ${OBJECTDIR}/_ext/1664057780/des3.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/des3.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/md5.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/md5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/md5.o.d" -o ${OBJECTDIR}/_ext/1664057780/md5.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md5.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/random.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/random.o.d" -o ${OBJECTDIR}/_ext/1664057780/random.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/random.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sha.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sha.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sha.o.d" -o ${OBJECTDIR}/_ext/1664057780/sha.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sha256.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sha256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sha256.o.d" -o ${OBJECTDIR}/_ext/1664057780/sha256.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha256.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sha512.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sha512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sha512.o.d" -o ${OBJECTDIR}/_ext/1664057780/sha512.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha512.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD4=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
else
${OBJECTDIR}/_ext/1664057780/misc.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/misc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/misc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/misc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/misc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/misc.o.d" -o ${OBJECTDIR}/_ext/1664057780/misc.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/misc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/978308758/bsp.o: ../src/config/pic32mz_ef_sk/bsp/bsp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/978308758" 
	@${RM} ${OBJECTDIR}/_ext/978308758/bsp.o.d 
	@${RM} ${OBJECTDIR}/_ext/978308758/bsp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/978308758/bsp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/978308758/bsp.o.d" -o ${OBJECTDIR}/_ext/978308758/bsp.o ../src/config/pic32mz_ef_sk/bsp/bsp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1997391349/crypto.o: ../src/config/pic32mz_ef_sk/crypto/src/crypto.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1997391349" 
	@${RM} ${OBJECTDIR}/_ext/1997391349/crypto.o.d 
	@${RM} ${OBJECTDIR}/_ext/1997391349/crypto.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1997391349/crypto.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1997391349/crypto.o.d" -o ${OBJECTDIR}/_ext/1997391349/crypto.o ../src/config/pic32mz_ef_sk/crypto/src/crypto.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1314174413/drv_ethmac.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_ethmac.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_ethmac.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_ethmac_lib.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_ethmac_lib.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o: ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1314174413" 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d 
	@${RM} ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o.d" -o ${OBJECTDIR}/_ext/1314174413/drv_eth_pic32_lib.o ../src/config/pic32mz_ef_sk/driver/ethmac/src/dynamic/drv_eth_pic32_lib.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/138020607/drv_ethphy.o: ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/138020607" 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_ethphy.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/138020607/drv_ethphy.o.d" -o ${OBJECTDIR}/_ext/138020607/drv_ethphy.o ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_ethphy.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o: ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/138020607" 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d 
	@${RM} ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o.d" -o ${OBJECTDIR}/_ext/138020607/drv_extphy_smsc8740.o ../src/config/pic32mz_ef_sk/driver/ethphy/src/dynamic/drv_extphy_smsc8740.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1520632/drv_memory.o: ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1520632" 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1520632/drv_memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1520632/drv_memory.o.d" -o ${OBJECTDIR}/_ext/1520632/drv_memory.o ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o: ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_file_system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1520632" 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o.d 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o.d" -o ${OBJECTDIR}/_ext/1520632/drv_memory_file_system.o ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_file_system.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o: ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1520632" 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o.d" -o ${OBJECTDIR}/_ext/1520632/drv_memory_nvm.o ../src/config/pic32mz_ef_sk/driver/memory/src/drv_memory_nvm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1761147401/drv_miim.o: ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1761147401" 
	@${RM} ${OBJECTDIR}/_ext/1761147401/drv_miim.o.d 
	@${RM} ${OBJECTDIR}/_ext/1761147401/drv_miim.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1761147401/drv_miim.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1761147401/drv_miim.o.d" -o ${OBJECTDIR}/_ext/1761147401/drv_miim.o ../src/config/pic32mz_ef_sk/driver/miim/src/dynamic/drv_miim.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/584638298/sys_fs_shell.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/common/sys_fs_shell.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/584638298" 
	@${RM} ${OBJECTDIR}/_ext/584638298/sys_fs_shell.o.d 
	@${RM} ${OBJECTDIR}/_ext/584638298/sys_fs_shell.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/584638298/sys_fs_shell.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/584638298/sys_fs_shell.o.d" -o ${OBJECTDIR}/_ext/584638298/sys_fs_shell.o ../src/config/pic32mz_ef_sk/library/tcpip/src/common/sys_fs_shell.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/helpers.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/helpers.o.d" -o ${OBJECTDIR}/_ext/2027382860/helpers.o ../src/config/pic32mz_ef_sk/library/tcpip/src/helpers.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/dns.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dns.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/dns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/dns.o.d" -o ${OBJECTDIR}/_ext/2027382860/dns.o ../src/config/pic32mz_ef_sk/library/tcpip/src/dns.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/icmp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/icmp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/icmp.o.d" -o ${OBJECTDIR}/_ext/2027382860/icmp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/icmp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/nbns.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/nbns.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/nbns.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/nbns.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/nbns.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/nbns.o.d" -o ${OBJECTDIR}/_ext/2027382860/nbns.o ../src/config/pic32mz_ef_sk/library/tcpip/src/nbns.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcp.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/dhcp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dhcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/dhcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/dhcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/dhcp.o.d" -o ${OBJECTDIR}/_ext/2027382860/dhcp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/dhcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/arp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/arp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/arp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/arp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/arp.o.d" -o ${OBJECTDIR}/_ext/2027382860/arp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/arp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/icmpv6.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/icmpv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmpv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/icmpv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/icmpv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/icmpv6.o.d" -o ${OBJECTDIR}/_ext/2027382860/icmpv6.o ../src/config/pic32mz_ef_sk/library/tcpip/src/icmpv6.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/ndp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/ndp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ndp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ndp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/ndp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/ndp.o.d" -o ${OBJECTDIR}/_ext/2027382860/ndp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/ndp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_commands.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_commands.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_commands.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_commands.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/ipv6.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv6.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv6.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/ipv6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/ipv6.o.d" -o ${OBJECTDIR}/_ext/2027382860/ipv6.o ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv6.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/http.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/http.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/http.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/http.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/http.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/http.o.d" -o ${OBJECTDIR}/_ext/2027382860/http.o ../src/config/pic32mz_ef_sk/library/tcpip/src/http.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/ipv4.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv4.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/ipv4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/ipv4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/ipv4.o.d" -o ${OBJECTDIR}/_ext/2027382860/ipv4.o ../src/config/pic32mz_ef_sk/library/tcpip/src/ipv4.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/smtpc.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/smtpc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/smtpc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/smtpc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/smtpc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/smtpc.o.d" -o ${OBJECTDIR}/_ext/2027382860/smtpc.o ../src/config/pic32mz_ef_sk/library/tcpip/src/smtpc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_alloc.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_alloc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_heap_internal.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_heap_internal.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/hash_fnv.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/hash_fnv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/hash_fnv.o.d" -o ${OBJECTDIR}/_ext/2027382860/hash_fnv.o ../src/config/pic32mz_ef_sk/library/tcpip/src/hash_fnv.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/oahash.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/oahash.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/oahash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/oahash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/oahash.o.d" -o ${OBJECTDIR}/_ext/2027382860/oahash.o ../src/config/pic32mz_ef_sk/library/tcpip/src/oahash.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_helpers.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_helpers.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_manager.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_manager.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_manager.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_manager.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_notify.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_notify.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_notify.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_notify.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_packet.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_packet.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_packet.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_packet.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/sntp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/sntp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/sntp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/sntp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/sntp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/sntp.o.d" -o ${OBJECTDIR}/_ext/2027382860/sntp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/sntp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/tcpip_announce.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_announce.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/tcpip_announce.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/tcpip_announce.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/tcpip_announce.o.d" -o ${OBJECTDIR}/_ext/2027382860/tcpip_announce.o ../src/config/pic32mz_ef_sk/library/tcpip/src/tcpip_announce.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2027382860/udp.o: ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2027382860" 
	@${RM} ${OBJECTDIR}/_ext/2027382860/udp.o.d 
	@${RM} ${OBJECTDIR}/_ext/2027382860/udp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2027382860/udp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2027382860/udp.o.d" -o ${OBJECTDIR}/_ext/2027382860/udp.o ../src/config/pic32mz_ef_sk/library/tcpip/src/udp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/513706829/net_pres.o: ../src/config/pic32mz_ef_sk/net_pres/pres/src/net_pres.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/513706829" 
	@${RM} ${OBJECTDIR}/_ext/513706829/net_pres.o.d 
	@${RM} ${OBJECTDIR}/_ext/513706829/net_pres.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/513706829/net_pres.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/513706829/net_pres.o.d" -o ${OBJECTDIR}/_ext/513706829/net_pres.o ../src/config/pic32mz_ef_sk/net_pres/pres/src/net_pres.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o: ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_enc_glue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1508781048" 
	@${RM} ${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o.d" -o ${OBJECTDIR}/_ext/1508781048/net_pres_enc_glue.o ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_enc_glue.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o: ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_cert_store.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1508781048" 
	@${RM} ${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o.d 
	@${RM} ${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o.d" -o ${OBJECTDIR}/_ext/1508781048/net_pres_cert_store.o ../src/config/pic32mz_ef_sk/net_pres/pres/net_pres_cert_store.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1098417660/plib_clk.o: ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1098417660" 
	@${RM} ${OBJECTDIR}/_ext/1098417660/plib_clk.o.d 
	@${RM} ${OBJECTDIR}/_ext/1098417660/plib_clk.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1098417660/plib_clk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1098417660/plib_clk.o.d" -o ${OBJECTDIR}/_ext/1098417660/plib_clk.o ../src/config/pic32mz_ef_sk/peripheral/clk/plib_clk.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1710852712/plib_coretimer.o: ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1710852712" 
	@${RM} ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1710852712/plib_coretimer.o.d" -o ${OBJECTDIR}/_ext/1710852712/plib_coretimer.o ../src/config/pic32mz_ef_sk/peripheral/coretimer/plib_coretimer.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/308860137/plib_evic.o: ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/308860137" 
	@${RM} ${OBJECTDIR}/_ext/308860137/plib_evic.o.d 
	@${RM} ${OBJECTDIR}/_ext/308860137/plib_evic.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/308860137/plib_evic.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/308860137/plib_evic.o.d" -o ${OBJECTDIR}/_ext/308860137/plib_evic.o ../src/config/pic32mz_ef_sk/peripheral/evic/plib_evic.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/308913965/plib_gpio.o: ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/308913965" 
	@${RM} ${OBJECTDIR}/_ext/308913965/plib_gpio.o.d 
	@${RM} ${OBJECTDIR}/_ext/308913965/plib_gpio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/308913965/plib_gpio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/308913965/plib_gpio.o.d" -o ${OBJECTDIR}/_ext/308913965/plib_gpio.o ../src/config/pic32mz_ef_sk/peripheral/gpio/plib_gpio.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1098406777/plib_nvm.o: ../src/config/pic32mz_ef_sk/peripheral/nvm/plib_nvm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1098406777" 
	@${RM} ${OBJECTDIR}/_ext/1098406777/plib_nvm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1098406777/plib_nvm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1098406777/plib_nvm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1098406777/plib_nvm.o.d" -o ${OBJECTDIR}/_ext/1098406777/plib_nvm.o ../src/config/pic32mz_ef_sk/peripheral/nvm/plib_nvm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/309316908/plib_uart2.o: ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/309316908" 
	@${RM} ${OBJECTDIR}/_ext/309316908/plib_uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/309316908/plib_uart2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/309316908/plib_uart2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/309316908/plib_uart2.o.d" -o ${OBJECTDIR}/_ext/309316908/plib_uart2.o ../src/config/pic32mz_ef_sk/peripheral/uart/plib_uart2.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/458842868/xc32_monitor.o: ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/458842868" 
	@${RM} ${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/458842868/xc32_monitor.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/458842868/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/458842868/xc32_monitor.o ../src/config/pic32mz_ef_sk/stdio/xc32_monitor.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/2135388491/sys_command.o: ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2135388491" 
	@${RM} ${OBJECTDIR}/_ext/2135388491/sys_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/2135388491/sys_command.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2135388491/sys_command.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/2135388491/sys_command.o.d" -o ${OBJECTDIR}/_ext/2135388491/sys_command.o ../src/config/pic32mz_ef_sk/system/command/src/sys_command.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1702866625/sys_console.o: ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1702866625" 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console.o.d 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1702866625/sys_console.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1702866625/sys_console.o.d" -o ${OBJECTDIR}/_ext/1702866625/sys_console.o ../src/config/pic32mz_ef_sk/system/console/src/sys_console.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1702866625/sys_console_uart.o: ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1702866625" 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1702866625/sys_console_uart.o.d" -o ${OBJECTDIR}/_ext/1702866625/sys_console_uart.o ../src/config/pic32mz_ef_sk/system/console/src/sys_console_uart.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/57023747/sys_debug.o: ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/57023747" 
	@${RM} ${OBJECTDIR}/_ext/57023747/sys_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/57023747/sys_debug.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/57023747/sys_debug.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/57023747/sys_debug.o.d" -o ${OBJECTDIR}/_ext/57023747/sys_debug.o ../src/config/pic32mz_ef_sk/system/debug/src/sys_debug.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/641613919/ff.o: ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/ff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/641613919" 
	@${RM} ${OBJECTDIR}/_ext/641613919/ff.o.d 
	@${RM} ${OBJECTDIR}/_ext/641613919/ff.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/641613919/ff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/641613919/ff.o.d" -o ${OBJECTDIR}/_ext/641613919/ff.o ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/ff.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/641613919/diskio.o: ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/diskio.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/641613919" 
	@${RM} ${OBJECTDIR}/_ext/641613919/diskio.o.d 
	@${RM} ${OBJECTDIR}/_ext/641613919/diskio.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/641613919/diskio.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/641613919/diskio.o.d" -o ${OBJECTDIR}/_ext/641613919/diskio.o ../src/config/pic32mz_ef_sk/system/fs/fat_fs/src/diskio.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/883137948/mpfs.o: ../src/config/pic32mz_ef_sk/system/fs/mpfs/src/mpfs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/883137948" 
	@${RM} ${OBJECTDIR}/_ext/883137948/mpfs.o.d 
	@${RM} ${OBJECTDIR}/_ext/883137948/mpfs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/883137948/mpfs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/883137948/mpfs.o.d" -o ${OBJECTDIR}/_ext/883137948/mpfs.o ../src/config/pic32mz_ef_sk/system/fs/mpfs/src/mpfs.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1879727853/sys_fs.o: ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1879727853" 
	@${RM} ${OBJECTDIR}/_ext/1879727853/sys_fs.o.d 
	@${RM} ${OBJECTDIR}/_ext/1879727853/sys_fs.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1879727853/sys_fs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1879727853/sys_fs.o.d" -o ${OBJECTDIR}/_ext/1879727853/sys_fs.o ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o: ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs_media_manager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1879727853" 
	@${RM} ${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o.d 
	@${RM} ${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o.d" -o ${OBJECTDIR}/_ext/1879727853/sys_fs_media_manager.o ../src/config/pic32mz_ef_sk/system/fs/src/sys_fs_media_manager.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/723085273/sys_int.o: ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/723085273" 
	@${RM} ${OBJECTDIR}/_ext/723085273/sys_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/723085273/sys_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/723085273/sys_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/723085273/sys_int.o.d" -o ${OBJECTDIR}/_ext/723085273/sys_int.o ../src/config/pic32mz_ef_sk/system/int/src/sys_int.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1658225107/sys_time.o: ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1658225107" 
	@${RM} ${OBJECTDIR}/_ext/1658225107/sys_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1658225107/sys_time.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1658225107/sys_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1658225107/sys_time.o.d" -o ${OBJECTDIR}/_ext/1658225107/sys_time.o ../src/config/pic32mz_ef_sk/system/time/src/sys_time.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o: ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1344301860" 
	@${RM} ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d 
	@${RM} ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o.d" -o ${OBJECTDIR}/_ext/1344301860/sys_time_h2_adapter.o ../src/config/pic32mz_ef_sk/system/sys_time_h2_adapter.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/942849350/tasks.o: ../src/config/pic32mz_ef_sk/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/tasks.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/942849350/tasks.o.d" -o ${OBJECTDIR}/_ext/942849350/tasks.o ../src/config/pic32mz_ef_sk/tasks.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/942849350/initialization.o: ../src/config/pic32mz_ef_sk/initialization.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/initialization.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/initialization.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/942849350/initialization.o.d" -o ${OBJECTDIR}/_ext/942849350/initialization.o ../src/config/pic32mz_ef_sk/initialization.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/942849350/interrupts.o: ../src/config/pic32mz_ef_sk/interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/interrupts.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/interrupts.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/942849350/interrupts.o.d" -o ${OBJECTDIR}/_ext/942849350/interrupts.o ../src/config/pic32mz_ef_sk/interrupts.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/942849350/exceptions.o: ../src/config/pic32mz_ef_sk/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/942849350" 
	@${RM} ${OBJECTDIR}/_ext/942849350/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/942849350/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/942849350/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/942849350/exceptions.o.d" -o ${OBJECTDIR}/_ext/942849350/exceptions.o ../src/config/pic32mz_ef_sk/exceptions.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/108032392/dialtek_modbus.o: ../src/modbus/dialtek_modbus.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/108032392" 
	@${RM} ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d 
	@${RM} ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/108032392/dialtek_modbus.o.d" -o ${OBJECTDIR}/_ext/108032392/dialtek_modbus.o ../src/modbus/dialtek_modbus.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/modbus_app.o: ../src/modbus_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/modbus_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/modbus_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/modbus_app.o ../src/modbus_app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o: ../src/modbus_buf_tcp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o.d" -o ${OBJECTDIR}/_ext/1360937237/modbus_buf_tcp.o ../src/modbus_buf_tcp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o: ../src/PIC32MZ_SPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o.d" -o ${OBJECTDIR}/_ext/1360937237/PIC32MZ_SPI.o ../src/PIC32MZ_SPI.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/d_eeprom.o: ../src/d_eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/d_eeprom.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/d_eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/d_eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/d_eeprom.o.d" -o ${OBJECTDIR}/_ext/1360937237/d_eeprom.o ../src/d_eeprom.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o: ../src/PIC32MZ_UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o.d" -o ${OBJECTDIR}/_ext/1360937237/PIC32MZ_UART.o ../src/PIC32MZ_UART.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/mpfs_img2.o: ../src/mpfs_img2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/mpfs_img2.o.d" -o ${OBJECTDIR}/_ext/1360937237/mpfs_img2.o ../src/mpfs_img2.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/http_print.o: ../src/http_print.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_print.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_print.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/http_print.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/http_print.o.d" -o ${OBJECTDIR}/_ext/1360937237/http_print.o ../src/http_print.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/custom_http_app.o: ../src/custom_http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/custom_http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/custom_http_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/custom_http_app.o ../src/custom_http_app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/http_app.o: ../src/http_app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/http_app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/http_app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/http_app.o.d" -o ${OBJECTDIR}/_ext/1360937237/http_app.o ../src/http_app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/pic32mz-crypt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o.d" -o ${OBJECTDIR}/_ext/172253694/pic32mz-crypt.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/pic32mz-crypt.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_sam6149.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_aes_sam6149.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_sam6149.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_u2238.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_aes_u2238.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_aes_u2238.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_ecc_pukcl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_ecc_pukcl.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_ecc_pukcl.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_pukcl_functions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_pukcl_functions.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_pukcl_functions.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_sam6334.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_rng_sam6334.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_sam6334.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_u2242.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_rng_u2242.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rng_u2242.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rsa_pukcl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_rsa_pukcl.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_rsa_pukcl.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam11105.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam11105.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam11105.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha1_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha1_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam11105.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam11105.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam11105.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha224_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha224_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam11105.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam11105.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam11105.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha256_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha256_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha384_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha384_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha384_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha512_sam6156.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_sha512_sam6156.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_sha512_sam6156.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_tdes_sam6150.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_tdes_sam6150.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_tdes_sam6150.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_wolfcryptcb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/172253694" 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o.d 
	@${RM} ${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o.d" -o ${OBJECTDIR}/_ext/172253694/crypt_wolfcryptcb.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/port/pic32/crypt_wolfcryptcb.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/arc4.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/arc4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/arc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/arc4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/arc4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/arc4.o.d" -o ${OBJECTDIR}/_ext/1664057780/arc4.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/arc4.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/asm.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/asm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/asm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/asm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/asm.o.d" -o ${OBJECTDIR}/_ext/1664057780/asm.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/asn.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asn.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/asn.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/asn.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/asn.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/asn.o.d" -o ${OBJECTDIR}/_ext/1664057780/asn.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/asn.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/blake2b.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2b.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/blake2b.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/blake2b.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/blake2b.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/blake2b.o.d" -o ${OBJECTDIR}/_ext/1664057780/blake2b.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2b.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/blake2s.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2s.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/blake2s.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/blake2s.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/blake2s.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/blake2s.o.d" -o ${OBJECTDIR}/_ext/1664057780/blake2s.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/blake2s.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/camellia.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/camellia.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/camellia.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/camellia.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/camellia.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/camellia.o.d" -o ${OBJECTDIR}/_ext/1664057780/camellia.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/camellia.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/chacha.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/chacha.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/chacha.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/chacha.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/chacha.o.d" -o ${OBJECTDIR}/_ext/1664057780/chacha.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha20_poly1305.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o.d" -o ${OBJECTDIR}/_ext/1664057780/chacha20_poly1305.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/chacha20_poly1305.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/cmac.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/cmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/cmac.o.d" -o ${OBJECTDIR}/_ext/1664057780/cmac.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cmac.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/coding.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/coding.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/coding.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/coding.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/coding.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/coding.o.d" -o ${OBJECTDIR}/_ext/1664057780/coding.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/coding.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/compress.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/compress.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/compress.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/compress.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/compress.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/compress.o.d" -o ${OBJECTDIR}/_ext/1664057780/compress.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/compress.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/cpuid.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cpuid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cpuid.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cpuid.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/cpuid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/cpuid.o.d" -o ${OBJECTDIR}/_ext/1664057780/cpuid.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cpuid.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/cryptocb.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cryptocb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cryptocb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/cryptocb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/cryptocb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/cryptocb.o.d" -o ${OBJECTDIR}/_ext/1664057780/cryptocb.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/cryptocb.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/curve25519.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/curve25519.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/curve25519.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/curve25519.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/curve25519.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/curve25519.o.d" -o ${OBJECTDIR}/_ext/1664057780/curve25519.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/curve25519.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/dh.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dh.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/dh.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/dh.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/dh.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/dh.o.d" -o ${OBJECTDIR}/_ext/1664057780/dh.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dh.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/dsa.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/dsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/dsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/dsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/dsa.o.d" -o ${OBJECTDIR}/_ext/1664057780/dsa.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/dsa.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ecc.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ecc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ecc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ecc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ecc.o.d" -o ${OBJECTDIR}/_ext/1664057780/ecc.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ecc_fp.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc_fp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ecc_fp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ecc_fp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ecc_fp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ecc_fp.o.d" -o ${OBJECTDIR}/_ext/1664057780/ecc_fp.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ecc_fp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ed25519.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ed25519.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ed25519.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ed25519.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ed25519.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ed25519.o.d" -o ${OBJECTDIR}/_ext/1664057780/ed25519.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ed25519.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/error.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/error.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/error.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/error.o.d" -o ${OBJECTDIR}/_ext/1664057780/error.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/error.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/fe_low_mem.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_low_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/fe_low_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/fe_low_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/fe_low_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/fe_low_mem.o.d" -o ${OBJECTDIR}/_ext/1664057780/fe_low_mem.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_low_mem.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/fe_operations.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_operations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/fe_operations.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/fe_operations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/fe_operations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/fe_operations.o.d" -o ${OBJECTDIR}/_ext/1664057780/fe_operations.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/fe_operations.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ge_low_mem.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_low_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ge_low_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ge_low_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ge_low_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ge_low_mem.o.d" -o ${OBJECTDIR}/_ext/1664057780/ge_low_mem.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_low_mem.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ge_operations.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_operations.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ge_operations.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ge_operations.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ge_operations.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ge_operations.o.d" -o ${OBJECTDIR}/_ext/1664057780/ge_operations.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ge_operations.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/hash.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hash.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hash.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/hash.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/hash.o.d" -o ${OBJECTDIR}/_ext/1664057780/hash.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hash.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/hc128.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hc128.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hc128.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hc128.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/hc128.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/hc128.o.d" -o ${OBJECTDIR}/_ext/1664057780/hc128.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hc128.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/hmac.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hmac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/hmac.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/hmac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/hmac.o.d" -o ${OBJECTDIR}/_ext/1664057780/hmac.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/hmac.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/idea.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/idea.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/idea.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/idea.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/idea.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/idea.o.d" -o ${OBJECTDIR}/_ext/1664057780/idea.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/idea.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/integer.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/integer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/integer.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/integer.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/integer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/integer.o.d" -o ${OBJECTDIR}/_ext/1664057780/integer.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/integer.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/logging.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/logging.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/logging.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/logging.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/logging.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/logging.o.d" -o ${OBJECTDIR}/_ext/1664057780/logging.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/logging.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/md2.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md2.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/md2.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/md2.o.d" -o ${OBJECTDIR}/_ext/1664057780/md2.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md2.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/md4.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md4.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md4.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/md4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/md4.o.d" -o ${OBJECTDIR}/_ext/1664057780/md4.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md4.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/memory.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/memory.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/memory.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/memory.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/memory.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/memory.o.d" -o ${OBJECTDIR}/_ext/1664057780/memory.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/memory.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/pkcs12.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pkcs12.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pkcs12.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/pkcs12.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/pkcs12.o.d" -o ${OBJECTDIR}/_ext/1664057780/pkcs12.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs12.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/pkcs7.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs7.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pkcs7.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pkcs7.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/pkcs7.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/pkcs7.o.d" -o ${OBJECTDIR}/_ext/1664057780/pkcs7.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pkcs7.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/poly1305.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/poly1305.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/poly1305.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/poly1305.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/poly1305.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/poly1305.o.d" -o ${OBJECTDIR}/_ext/1664057780/poly1305.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/poly1305.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/pwdbased.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pwdbased.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pwdbased.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/pwdbased.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/pwdbased.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/pwdbased.o.d" -o ${OBJECTDIR}/_ext/1664057780/pwdbased.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/pwdbased.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/rabbit.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rabbit.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/rabbit.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/rabbit.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/rabbit.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/rabbit.o.d" -o ${OBJECTDIR}/_ext/1664057780/rabbit.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rabbit.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/ripemd.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ripemd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ripemd.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/ripemd.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/ripemd.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/ripemd.o.d" -o ${OBJECTDIR}/_ext/1664057780/ripemd.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/ripemd.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/rsa.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rsa.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/rsa.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/rsa.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/rsa.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/rsa.o.d" -o ${OBJECTDIR}/_ext/1664057780/rsa.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/rsa.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sha3.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sha3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sha3.o.d" -o ${OBJECTDIR}/_ext/1664057780/sha3.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha3.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/signature.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/signature.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/signature.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/signature.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/signature.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/signature.o.d" -o ${OBJECTDIR}/_ext/1664057780/signature.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/signature.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_arm32.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_arm32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_arm32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_arm32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_arm32.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_arm32.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm32.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_arm64.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_arm64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_arm64.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_arm64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_arm64.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_arm64.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_arm64.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_armthumb.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_armthumb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_armthumb.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_armthumb.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_armthumb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_armthumb.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_armthumb.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_armthumb.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_c32.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_c32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_c32.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_c32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_c32.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_c32.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c32.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_c64.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_c64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_c64.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_c64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_c64.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_c64.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_c64.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_cortexm.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_cortexm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_cortexm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_cortexm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_cortexm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_cortexm.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_cortexm.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_cortexm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_int.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_int.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_int.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_int.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_int.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_int.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_int.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_int.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sp_x86_64.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_x86_64.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_x86_64.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sp_x86_64.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sp_x86_64.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sp_x86_64.o.d" -o ${OBJECTDIR}/_ext/1664057780/sp_x86_64.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sp_x86_64.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/srp.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/srp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/srp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/srp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/srp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/srp.o.d" -o ${OBJECTDIR}/_ext/1664057780/srp.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/srp.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/tfm.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/tfm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/tfm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/tfm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/tfm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/tfm.o.d" -o ${OBJECTDIR}/_ext/1664057780/tfm.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/tfm.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wc_encrypt.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_encrypt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_encrypt.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_encrypt.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wc_encrypt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wc_encrypt.o.d" -o ${OBJECTDIR}/_ext/1664057780/wc_encrypt.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_encrypt.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_pkcs11.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o.d" -o ${OBJECTDIR}/_ext/1664057780/wc_pkcs11.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_pkcs11.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wc_port.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wc_port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wc_port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wc_port.o.d" -o ${OBJECTDIR}/_ext/1664057780/wc_port.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wc_port.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wolfevent.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfevent.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wolfevent.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wolfevent.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wolfevent.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wolfevent.o.d" -o ${OBJECTDIR}/_ext/1664057780/wolfevent.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfevent.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/wolfmath.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfmath.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wolfmath.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/wolfmath.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/wolfmath.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/wolfmath.o.d" -o ${OBJECTDIR}/_ext/1664057780/wolfmath.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/wolfmath.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/aes.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/aes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/aes.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/aes.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/aes.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/aes.o.d" -o ${OBJECTDIR}/_ext/1664057780/aes.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/aes.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/des3.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/des3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/des3.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/des3.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/des3.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/des3.o.d" -o ${OBJECTDIR}/_ext/1664057780/des3.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/des3.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/md5.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md5.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md5.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/md5.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/md5.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/md5.o.d" -o ${OBJECTDIR}/_ext/1664057780/md5.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/md5.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/random.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/random.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/random.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/random.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/random.o.d" -o ${OBJECTDIR}/_ext/1664057780/random.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/random.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sha.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sha.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sha.o.d" -o ${OBJECTDIR}/_ext/1664057780/sha.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sha256.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha256.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha256.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha256.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sha256.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sha256.o.d" -o ${OBJECTDIR}/_ext/1664057780/sha256.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha256.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1664057780/sha512.o: ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha512.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1664057780" 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha512.o.d 
	@${RM} ${OBJECTDIR}/_ext/1664057780/sha512.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1664057780/sha512.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1664057780/sha512.o.d" -o ${OBJECTDIR}/_ext/1664057780/sha512.o ../src/third_party/wolfssl/wolfssl/wolfcrypt/src/sha512.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/app.o: ../src/app.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/app.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/app.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/app.o.d" -o ${OBJECTDIR}/_ext/1360937237/app.o ../src/app.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1360937237/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -DHAVE_CONFIG_H -DWOLFSSL_IGNORE_FILE_WARN -I"../src/config/pic32mz_ef_sk/library" -I"../src/config/pic32mz_ef_sk/library/tcpip/src" -I"../src/config/pic32mz_ef_sk/library/tcpip/src/common" -I"../src" -I"../src/config/pic32mz_ef_sk" -I"../src/packs/PIC32MZ2048EFM144_DFP" -I"../src/mips" -I"../src/third_party/wolfssl" -I"../src/third_party/wolfssl/wolfssl" -I"../src/config/pic32mz_ef_sk/peripheral/uart" -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -mdfp=${DFP_DIR}  
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_ICD4=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x37F   -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_ICD4=1,--defsym=_min_heap_size=55000,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp=${DFP_DIR}
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/pic32mz_ef_sk.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_pic32mz_ef_sk=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=55000,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp=${DFP_DIR}
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
