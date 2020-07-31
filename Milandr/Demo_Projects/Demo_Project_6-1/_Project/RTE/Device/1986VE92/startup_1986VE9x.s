; *****************************************************************************
; * @File: startup_1986VE9x.s
; * @Author: Milandr, L.
; * @Project: Generic
; * @Microcontroller: 1986VE9x
; * @Date: 11.03.2020
; * @Purpose: Hardware configuration & MCU launching
; *****************************************************************************

; Amount of memory (in Bytes) allocated for Stack
Stack_Size      EQU     0x00000400
                AREA    STACK, NOINIT, READWRITE, ALIGN = 3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; Amount of memory (in Bytes) allocated for Heap
Heap_Size       EQU     0x00000200
                AREA    HEAP, NOINIT, READWRITE, ALIGN = 3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

;  Vector Table (mapped to address 0 at reset)
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

                ; Exceptions (internal)
__Vectors       DCD     __initial_sp               ; Top of the Stack
                DCD     Reset_Handler              ; Reset Handler
                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MPU Fault Handler
                DCD     BusFault_Handler           ; Bus Fault Handler
                DCD     UsageFault_Handler         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; Interrupts (external)
                DCD     CAN1_IRQHandler            ; IRQ0
                DCD     CAN2_IRQHandler            ; IRQ1
                DCD     USB_IRQHandler             ; IRQ2
                DCD     0                          ; IRQ3 Reserved
                DCD     0                          ; IRQ4 Reserved
                DCD     DMA_IRQHandler             ; IRQ5
                DCD     UART1_IRQHandler           ; IRQ6
                DCD     UART2_IRQHandler           ; IRQ7
                DCD     SSP1_IRQHandler            ; IRQ8
                DCD     0                          ; IRQ9 Reserved
                DCD     I2C_IRQHandler             ; IRQ10
                DCD     POWER_IRQHandler           ; IRQ11
                DCD     WWDG_IRQHandler            ; IRQ12
                DCD     0                          ; IRQ13 Reserved
                DCD     Timer1_IRQHandler          ; IRQ14
                DCD     Timer2_IRQHandler          ; IRQ15
                DCD     Timer3_IRQHandler          ; IRQ16
                DCD     ADC_IRQHandler             ; IRQ17
                DCD     0                          ; IRQ18 reserved
                DCD     COMPARATOR_IRQHandler      ; IRQ19
                DCD     SSP2_IRQHandler            ; IRQ20
                DCD     0                          ; IRQ21 Reserved
                DCD     0                          ; IRQ22 Reserved
                DCD     0                          ; IRQ23 Reserved
                DCD     0                          ; IRQ24 Reserved
                DCD     0                          ; IRQ25 Reserved
                DCD     0                          ; IRQ26 Reserved
                DCD     BACKUP_IRQHandler          ; IRQ27
                DCD     EXT_INT1_IRQHandler        ; IRQ28
                DCD     EXT_INT2_IRQHandler        ; IRQ29
                DCD     EXT_INT3_IRQHandler        ; IRQ30
                DCD     EXT_INT4_IRQHandler        ; IRQ31
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset Handler (application launching)
Reset_Handler    PROC
                 EXPORT  Reset_Handler             [WEAK]

                 IMPORT  __main
                 LDR     R0, =__main
                 BX      R0
                 ENDP

; Exception Handlers (infinite loops which can be modified)
NMI_Handler\
                PROC
                EXPORT  NMI_Handler                [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler          [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler          [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler           [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler                [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler           [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler             [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler            [WEAK]
                B       .
                ENDP

Default_Handler\
                PROC

; Interrupt Handlers (empty bodies which can be modified)
                EXPORT  CAN1_IRQHandler            [WEAK]
                EXPORT  CAN2_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler             [WEAK]
                EXPORT  DMA_IRQHandler             [WEAK]
                EXPORT  UART1_IRQHandler           [WEAK]
                EXPORT  UART2_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler            [WEAK]
                EXPORT  I2C_IRQHandler             [WEAK]
                EXPORT  POWER_IRQHandler           [WEAK]
                EXPORT  WWDG_IRQHandler            [WEAK]
                EXPORT  Timer1_IRQHandler          [WEAK]
                EXPORT  Timer2_IRQHandler          [WEAK]
                EXPORT  Timer3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler             [WEAK]
                EXPORT  COMPARATOR_IRQHandler      [WEAK]
                EXPORT  SSP2_IRQHandler            [WEAK]
                EXPORT  BACKUP_IRQHandler          [WEAK]
                EXPORT  EXT_INT1_IRQHandler        [WEAK]
                EXPORT  EXT_INT2_IRQHandler        [WEAK]
                EXPORT  EXT_INT3_IRQHandler        [WEAK]
                EXPORT  EXT_INT4_IRQHandler        [WEAK]

CAN1_IRQHandler
CAN2_IRQHandler
USB_IRQHandler
DMA_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
SSP1_IRQHandler
I2C_IRQHandler
POWER_IRQHandler
WWDG_IRQHandler
Timer1_IRQHandler
Timer2_IRQHandler
Timer3_IRQHandler
ADC_IRQHandler
COMPARATOR_IRQHandler
SSP2_IRQHandler
BACKUP_IRQHandler
EXT_INT1_IRQHandler
EXT_INT2_IRQHandler
EXT_INT3_IRQHandler
EXT_INT4_IRQHandler

                B       .
                ENDP
                ALIGN

; Stack and Heap initialization
                 IF      :DEF:__MICROLIB

                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit

                 ELSE

                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap

__user_initial_stackheap
                 LDR     R0, =  Heap_Mem
                 LDR     R1, = (Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem  + Heap_Size)
                 LDR     R3, =  Stack_Mem
                 BX      LR

                 ALIGN
                 ENDIF

                 END
