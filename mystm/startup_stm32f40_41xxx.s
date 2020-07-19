.equ Stack_Size, 0x00000400 
.equ Heap_Size,  0x00000200 

.section .data 
.align(3)
Stack_Mem: .zero Stack_Size
__initial_sp:

.section .data 
.align(3)
__heap_base:
Heap_Mem: .zero Heap_Size
__heap_limit:
.thumb

.section .data 
.align(3)
.global __Vectors
.global __Vectors_End
.global __Vectors_Size
__Vectors:
	.long     __initial_sp               		@ Top of Stack
    .long     Reset_Handler              		@ Reset Handler
    .long     NMI_Handler                		@ NMI Handler
    .long     HardFault_Handler          		@ Hard Fault Handler
    .long     MemManage_Handler          		@ MPU Fault Handler
    .long     BusFault_Handler           		@ Bus Fault Handler
    .long     UsageFault_Handler         		@ Usage Fault Handler
    .long     0                          		@ Reserved
    .long     0                          		@ Reserved
    .long     0                          		@ Reserved
    .long     0                          		@ Reserved
    .long     SVC_Handler                		@ SVCall Handler
    .long     DebugMon_Handler           		@ Debug Monitor Handler
    .long     0                          		@ Reserved
    .long     PendSV_Handler             		@ PendSV Handler
    .long     SysTick_Handler            		@ SysTick Handler
		
    @ External Interrupts
    .long     WWDG_IRQHandler                   @ Window WatchDog                                        
    .long     PVD_IRQHandler                    @ PVD through EXTI Line detection                        
    .long     TAMP_STAMP_IRQHandler             @ Tamper and TimeStamps through the EXTI line            
    .long     RTC_WKUP_IRQHandler               @ RTC Wakeup through the EXTI line                       
    .long     FLASH_IRQHandler                  @ FLASH                                           
    .long     RCC_IRQHandler                    @ RCC                                             
    .long     EXTI0_IRQHandler                  @ EXTI Line0                                             
    .long     EXTI1_IRQHandler                  @ EXTI Line1                                             
    .long     EXTI2_IRQHandler                  @ EXTI Line2                                             
    .long     EXTI3_IRQHandler                  @ EXTI Line3                                             
    .long     EXTI4_IRQHandler                  @ EXTI Line4                                             
    .long     DMA1_Stream0_IRQHandler           @ DMA1 Stream 0                                   
    .long     DMA1_Stream1_IRQHandler           @ DMA1 Stream 1                                   
    .long     DMA1_Stream2_IRQHandler           @ DMA1 Stream 2                                   
    .long     DMA1_Stream3_IRQHandler           @ DMA1 Stream 3                                   
    .long     DMA1_Stream4_IRQHandler           @ DMA1 Stream 4                                   
    .long     DMA1_Stream5_IRQHandler           @ DMA1 Stream 5                                   
    .long     DMA1_Stream6_IRQHandler           @ DMA1 Stream 6                                   
    .long     ADC_IRQHandler                    @ ADC1, ADC2 and ADC3s                            
    .long     CAN1_TX_IRQHandler                @ CAN1 TX                                                
    .long     CAN1_RX0_IRQHandler               @ CAN1 RX0                                               
    .long     CAN1_RX1_IRQHandler               @ CAN1 RX1                                               
    .long     CAN1_SCE_IRQHandler               @ CAN1 SCE                                               
    .long     EXTI9_5_IRQHandler                @ External Line[9:5]s                                    
    .long     TIM1_BRK_TIM9_IRQHandler          @ TIM1 Break and TIM9                   
    .long     TIM1_UP_TIM10_IRQHandler          @ TIM1 Update and TIM10                 
    .long     TIM1_TRG_COM_TIM11_IRQHandler     @ TIM1 Trigger and Commutation and TIM11
    .long     TIM1_CC_IRQHandler                @ TIM1 Capture Compare                                   
    .long     TIM2_IRQHandler                   @ TIM2                                            
    .long     TIM3_IRQHandler                   @ TIM3                                            
    .long     TIM4_IRQHandler                   @ TIM4                                            
    .long     I2C1_EV_IRQHandler                @ I2C1 Event                                             
    .long     I2C1_ER_IRQHandler                @ I2C1 Error                                             
    .long     I2C2_EV_IRQHandler                @ I2C2 Event                                             
    .long     I2C2_ER_IRQHandler                @ I2C2 Error                                               
    .long     SPI1_IRQHandler                   @ SPI1                                            
    .long     SPI2_IRQHandler                   @ SPI2                                            
    .long     USART1_IRQHandler                 @ USART1                                          
    .long     USART2_IRQHandler                 @ USART2                                          
    .long     USART3_IRQHandler                 @ USART3                                          
    .long     EXTI15_10_IRQHandler              @ External Line[15:10]s                                  
    .long     RTC_Alarm_IRQHandler              @ RTC Alarm (A and B) through EXTI Line                  
    .long     OTG_FS_WKUP_IRQHandler            @ USB OTG FS Wakeup through EXTI line                        
    .long     TIM8_BRK_TIM12_IRQHandler         @ TIM8 Break and TIM12                  
    .long     TIM8_UP_TIM13_IRQHandler          @ TIM8 Update and TIM13                 
    .long     TIM8_TRG_COM_TIM14_IRQHandler     @ TIM8 Trigger and Commutation and TIM14
    .long     TIM8_CC_IRQHandler                @ TIM8 Capture Compare                                   
    .long     DMA1_Stream7_IRQHandler           @ DMA1 Stream7                                           
    .long     FSMC_IRQHandler                   @ FSMC                                            
    .long     SDIO_IRQHandler                   @ SDIO                                            
    .long     TIM5_IRQHandler                   @ TIM5                                            
    .long     SPI3_IRQHandler                   @ SPI3                                            
    .long     UART4_IRQHandler                  @ UART4                                           
    .long     UART5_IRQHandler                  @ UART5                                           
    .long     TIM6_DAC_IRQHandler               @ TIM6 and DAC1&2 underrun errors                   
    .long     TIM7_IRQHandler                   @ TIM7                   
    .long     DMA2_Stream0_IRQHandler           @ DMA2 Stream 0                                   
    .long     DMA2_Stream1_IRQHandler           @ DMA2 Stream 1                                   
    .long     DMA2_Stream2_IRQHandler           @ DMA2 Stream 2                                   
    .long     DMA2_Stream3_IRQHandler           @ DMA2 Stream 3                                   
    .long     DMA2_Stream4_IRQHandler           @ DMA2 Stream 4                                   
    .long     ETH_IRQHandler                    @ Ethernet                                        
    .long     ETH_WKUP_IRQHandler               @ Ethernet Wakeup through EXTI line                      
    .long     CAN2_TX_IRQHandler                @ CAN2 TX                                                
    .long     CAN2_RX0_IRQHandler               @ CAN2 RX0                                               
    .long     CAN2_RX1_IRQHandler               @ CAN2 RX1                                               
    .long     CAN2_SCE_IRQHandler               @ CAN2 SCE                                               
    .long     OTG_FS_IRQHandler                 @ USB OTG FS                                      
    .long     DMA2_Stream5_IRQHandler           @ DMA2 Stream 5                                   
    .long     DMA2_Stream6_IRQHandler           @ DMA2 Stream 6                                   
    .long     DMA2_Stream7_IRQHandler           @ DMA2 Stream 7                                   
    .long     USART6_IRQHandler                 @ USART6                                           
    .long     I2C3_EV_IRQHandler                @ I2C3 event                                             
    .long     I2C3_ER_IRQHandler                @ I2C3 error                                             
    .long     OTG_HS_EP1_OUT_IRQHandler         @ USB OTG HS End Point 1 Out                      
    .long     OTG_HS_EP1_IN_IRQHandler          @ USB OTG HS End Point 1 In                       
    .long     OTG_HS_WKUP_IRQHandler            @ USB OTG HS Wakeup through EXTI                         
    .long     OTG_HS_IRQHandler                 @ USB OTG HS                                      
    .long     DCMI_IRQHandler                   @ DCMI                                            
    .long     CRYP_IRQHandler                   @ CRYP crypto                                     
    .long     HASH_RNG_IRQHandler               @ Hash and Rng
    .long     FPU_IRQHandler                    @ FPU
                                         
__Vectors_End:
.equ __Vectors_Size,  __Vectors_End - __Vectors 



.section .text

Reset_Handler:
.macro Reset_Handler
.global Reset_Handler
.extern SystemInit
.extern __main
ldr r0,=SystemInit
blx r0
ldr ro,=__main
bx r0
.endm

NMI_Handler:   
.macro NMI_Handler
 .global NMI_Handler 					.weak
 b .
.endm

HardFault_Handler:
 .macro HardFault_Handler
 .global  HardFault_Handler          	.weak
b .
.endm

MemManage_Handler:
.macro MemManage_Handler
.global  MemManage_Handler          	.weak
b .
.endm

BusFault_Handler:
.macro BusFault_Handler
.global  BusFault_Handler           	.weak
b .
.endm

UsageFault_Handler:
.macro UsageFault_Handler
.global  UsageFault_Handler         	.weak
b .
.endm

SVC_Handler:
.macro SVC_Handler
.global  SVC_Handler                	.weak
b .
.endm

DebugMon_Handler:
.macro DebugMon_Handler
.global  DebugMon_Handler           	.weak
b .
.endm

PendSV_Handler: 
.macro PendSV_Handler
.global  PendSV_Handler             	.weak
b .
.endm

SysTick_Handler:
.macro SysTick_Handler
.global  SysTick_Handler            	.weak
b .
.endm

WWDG_IRQHandler: 
.macro WWDG_IRQHandler
.global  WWDG_IRQHandler                .weak
b .
.endm  
                                                   
PVD_IRQHandler: 
.macro PVD_IRQHandler
.global  PVD_IRQHandler                 .weak 
b .
.endm 
       
TAMP_STAMP_IRQHandler: 
.macro TAMP_STAMP_IRQHandler
.global  TAMP_STAMP_IRQHandler          .weak
b .
.endm 
               
RTC_WKUP_IRQHandler:
.macro RTC_WKUP_IRQHandler
.global  RTC_WKUP_IRQHandler            .weak
b .
.endm 
                             
FLASH_IRQHandler: 
.macro FLASH_IRQHandler
.global  FLASH_IRQHandler               .weak
b .
.endm 
                                                   
RCC_IRQHandler: 
.macro RCC_IRQHandler
.global  RCC_IRQHandler                 .weak
b .
.endm 
                                                         
EXTI0_IRQHandler: 
.macro EXTI0_IRQHandler
.global  EXTI0_IRQHandler               .weak
b .
.endm 
                                                      
EXTI1_IRQHandler: 
.macro EXTI1_IRQHandler
.global  EXTI1_IRQHandler				.weak
b .
.endm 
                                                         
EXTI2_IRQHandler: 
.macro EXTI2_IRQHandler
.global  EXTI2_IRQHandler				.weak
b .
.endm  
                                                       
EXTI3_IRQHandler: 
.macro EXTI3_IRQHandler
.global  EXTI3_IRQHandler				.weak
b .
.endm 
                                                       
EXTI4_IRQHandler: 
.macro EXTI4_IRQHandler
.global  EXTI4_IRQHandler				.weak
b .
.endm 
                                                        
DMA1_Stream0_IRQHandler: 
.macro DMA1_Stream0_IRQHandler
.global  DMA1_Stream0_IRQHandler		.weak
b .
.endm
                                      
DMA1_Stream1_IRQHandler: 
.macro DMA1_Stream1_IRQHandler
.global  DMA1_Stream1_IRQHandler		.weak
b .
.endm
                                         
DMA1_Stream2_IRQHandler:  
.macro DMA1_Stream2_IRQHandler
.global  DMA1_Stream2_IRQHandler		.weak
b .
.endm
                                        
DMA1_Stream3_IRQHandler: 
.macro DMA1_Stream3_IRQHandler
.global  DMA1_Stream3_IRQHandler		.weak
b .
.endm
                                         
DMA1_Stream4_IRQHandler:
.macro DMA1_Stream4_IRQHandler
.global  DMA1_Stream4_IRQHandler		.weak
b .
.endm
                                          
DMA1_Stream5_IRQHandler: 
.macro DMA1_Stream5_IRQHandler
.global  DMA1_Stream5_IRQHandler		.weak
b .
.endm
                                         
DMA1_Stream6_IRQHandler:  
.macro DMA1_Stream6_IRQHandler
.global  DMA1_Stream6_IRQHandler		.weak
b .
.endm 
                                       
ADC_IRQHandler:        
.macro ADC_IRQHandler
.global  ADC_IRQHandler					.weak
b .
.endm
                                 
CAN1_TX_IRQHandler: 
.macro CAN1_TX_IRQHandler
.global  CAN1_TX_IRQHandler				.weak
b .
.endm
                                                           
CAN1_RX0_IRQHandler: 
.macro CAN1_RX0_IRQHandler
.global  CAN1_RX0_IRQHandler			.weak
b .
.endm
                                                         
CAN1_RX1_IRQHandler: 
.macro CAN1_RX1_IRQHandler
.global  CAN1_RX1_IRQHandler			.weak
b .
.endm
                                                          
CAN1_SCE_IRQHandler: 
.macro CAN1_SCE_IRQHandler
.global  CAN1_SCE_IRQHandler			.weak
b .
.endm
                                                          
EXTI9_5_IRQHandler: 
.macro EXTI9_5_IRQHandler
.global  EXTI9_5_IRQHandler				.weak
b .
.endm
                                               
TIM1_BRK_TIM9_IRQHandler:  
.macro TIM1_BRK_TIM9_IRQHandler
.global  TIM1_BRK_TIM9_IRQHandler		.weak
b .
.endm
                      
TIM1_UP_TIM10_IRQHandler: 
.macro TIM1_UP_TIM10_IRQHandler
.global  TIM1_UP_TIM10_IRQHandler		.weak
b .
.endm
                     
TIM1_TRG_COM_TIM11_IRQHandler: 
.macro TIM1_TRG_COM_TIM11_IRQHandler
.global  TIM1_TRG_COM_TIM11_IRQHandler	.weak
b .
.endm
 
TIM1_CC_IRQHandler:  
.macro TIM1_CC_IRQHandler
.global  TIM1_CC_IRQHandler				.weak
b .
.endm
                                             
TIM2_IRQHandler: 
.macro TIM2_IRQHandler
.global  TIM2_IRQHandler				.weak
b .
.endm
                                                          
TIM3_IRQHandler:
.macro TIM3_IRQHandler
.global  TIM3_IRQHandler				.weak
b .
.endm
                                                           
TIM4_IRQHandler: 
.macro TIM4_IRQHandler
.global  TIM4_IRQHandler				.weak
b .
.endm
                                                          
I2C1_EV_IRQHandler:
.macro I2C1_EV_IRQHandler
.global  I2C1_EV_IRQHandler				.weak
b .
.endm
                                                         
I2C1_ER_IRQHandler: 
.macro I2C1_ER_IRQHandler
.global  I2C1_ER_IRQHandler				.weak
b .
.endm
                                                        
I2C2_EV_IRQHandler: 
.macro I2C2_EV_IRQHandler
.global  I2C2_EV_IRQHandler				.weak
b .
.endm
                                                       
I2C2_ER_IRQHandler:
.macro I2C2_ER_IRQHandler
.global  I2C2_ER_IRQHandler				.weak
b .
.endm
                                                           
SPI1_IRQHandler:
.macro SPI1_IRQHandler
.global  SPI1_IRQHandler				.weak
b .
.endm
                                                          
SPI2_IRQHandler:
.macro SPI2_IRQHandler
.global  SPI2_IRQHandler				.weak
b .
.endm
                                                           
USART1_IRQHandler:
.macro USART1_IRQHandler
.global  USART1_IRQHandler				.weak
b .
.endm
                                                       
USART2_IRQHandler: 
.macro USART2_IRQHandler
.global  USART2_IRQHandler				.weak
b .
.endm
                                                      
USART3_IRQHandler:
.macro USART3_IRQHandler
.global  USART2_IRQHandler				.weak
b .
.endm
                                                      
EXTI15_10_IRQHandler: 
.macro EXTI15_10_IRQHandler
.global  EXTI15_10_IRQHandler			.weak
b .
.endm
                                           
RTC_Alarm_IRQHandler: 
.macro RTC_Alarm_IRQHandler
.global  RTC_Alarm_IRQHandler			.weak
b .
.endm
                           
OTG_FS_WKUP_IRQHandler: 
.macro OTG_FS_WKUP_IRQHandler
.global  OTG_FS_WKUP_IRQHandler			.weak
b .
.endm
                               
TIM8_BRK_TIM12_IRQHandler:
.macro TIM8_BRK_TIM12_IRQHandler
.global  TIM8_BRK_TIM12_IRQHandler		.weak
b .
.endm
                      
TIM8_UP_TIM13_IRQHandler:
.macro TIM8_UP_TIM13_IRQHandler
.global  TIM8_UP_TIM13_IRQHandler		.weak
b .
.endm
                       
TIM8_TRG_COM_TIM14_IRQHandler: 
.macro TIM8_TRG_COM_TIM14_IRQHandler
.global  TIM8_TRG_COM_TIM14_IRQHandler	.weak
b .
.endm
 
TIM8_CC_IRQHandler: 
.macro TIM8_CC_IRQHandler
.global  TIM8_CC_IRQHandler				.weak
b .
.endm
                                              
DMA1_Stream7_IRQHandler: 
.macro DMA1_Stream7_IRQHandler
.global  DMA1_Stream7_IRQHandler		.weak
b .
.endm
                                                
FSMC_IRQHandler: 
.macro FSMC_IRQHandler
.global  FSMC_IRQHandler				.weak
b .
.endm
                                                           
SDIO_IRQHandler: 
.macro SDIO_IRQHandler
.global  SDIO_IRQHandler				.weak
b .
.endm
                                                           
TIM5_IRQHandler:  
.macro TIM5_IRQHandler
.global  TIM5_IRQHandler				.weak
b .
.endm
                                                          
SPI3_IRQHandler:   
.macro SPI3_IRQHandler
.global  SPI3_IRQHandler				.weak
b .
.endm
                                                         
UART4_IRQHandler:  
.macro UART4_IRQHandler
.global  UART4_IRQHandler				.weak
b .
.endm
                                                        
UART5_IRQHandler: 
.macro UART5_IRQHandler
.global  UART5_IRQHandler				.weak
b .
.endm
                                                         
TIM6_DAC_IRQHandler: 
.macro TIM6_DAC_IRQHandler
.global  TIM6_DAC_IRQHandler			.weak
b .
.endm
                           
TIM7_IRQHandler:    
.macro TIM7_IRQHandler
.global  TIM7_IRQHandler				.weak
b .
.endm
                          
DMA2_Stream0_IRQHandler: 
.macro DMA2_Stream0_IRQHandler
.global  DMA2_Stream0_IRQHandler		.weak
b .
.endm
                                        
DMA2_Stream1_IRQHandler: 
.macro DMA2_Stream1_IRQHandler
.global  DMA2_Stream1_IRQHandler		.weak
b .
.endm
                                         
DMA2_Stream2_IRQHandler: 
.macro DMA2_Stream2_IRQHandler
.global  DMA2_Stream2_IRQHandler		.weak
b .
.endm
                                          
DMA2_Stream3_IRQHandler: 
.macro DMA2_Stream3_IRQHandler
.global  DMA2_Stream3_IRQHandler		.weak
b .
.endm
                                          
DMA2_Stream4_IRQHandler: 
.macro DMA2_Stream4_IRQHandler
.global  DMA2_Stream4_IRQHandler		.weak
b .
.endm
                                       
ETH_IRQHandler:   
.macro ETH_IRQHandler
.global  ETH_IRQHandler					.weak
b .
.endm
                                                      
ETH_WKUP_IRQHandler:  
.macro ETH_WKUP_IRQHandler
.global  ETH_WKUP_IRQHandler			.weak
b .
.endm
                              
CAN2_TX_IRQHandler:  
.macro CAN2_TX_IRQHandler
.global  CAN2_TX_IRQHandler				.weak
b .
.endm
                                                         
CAN2_RX0_IRQHandler:  
.macro CAN2_RX0_IRQHandler
.global  CAN2_RX0_IRQHandler			.weak
b .
.endm
                                                        
CAN2_RX1_IRQHandler:  
.macro CAN2_RX1_IRQHandler
.global  CAN2_RX1_IRQHandler			.weak
b .
.endm
                                                        
CAN2_SCE_IRQHandler:  
.macro CAN2_SCE_IRQHandler
.global  CAN2_SCE_IRQHandler			.weak
b .
.endm
                                                        
OTG_FS_IRQHandler: 
.macro OTG_FS_IRQHandler
.global  OTG_FS_IRQHandler				.weak
b .
.endm
                                                   
DMA2_Stream5_IRQHandler:  
.macro DMA2_Stream5_IRQHandler
.global  DMA2_Stream5_IRQHandler		.weak
b .
.endm
                                        
DMA2_Stream6_IRQHandler:  
.macro DMA2_Stream6_IRQHandler
.global  DMA2_Stream6_IRQHandler		.weak
b .
.endm
                                        
DMA2_Stream7_IRQHandler: 
.macro DMA2_Stream7_IRQHandler
.global  DMA2_Stream7_IRQHandler		.weak
b .
.endm
                                         
USART6_IRQHandler:  
.macro USART6_IRQHandler
.global  USART6_IRQHandler				.weak
b .
.endm
                                                      
I2C3_EV_IRQHandler: 
.macro I2C3_EV_IRQHandler
.global  I2C3_EV_IRQHandler				.weak
b .
.endm
                                                         
I2C3_ER_IRQHandler: 
.macro I2C3_ER_IRQHandler
.global  I2C3_ER_IRQHandler				.weak
b .
.endm
                                                         
OTG_HS_EP1_OUT_IRQHandler: 
.macro OTG_HS_EP1_OUT_IRQHandler
.global  OTG_HS_EP1_OUT_IRQHandler		.weak
b .
.endm
                          
OTG_HS_EP1_IN_IRQHandler: 
.macro OTG_HS_EP1_IN_IRQHandler
.global  OTG_HS_EP1_IN_IRQHandler		.weak
b .
.endm
                           
OTG_HS_WKUP_IRQHandler:  
.macro OTG_HS_WKUP_IRQHandler
.global  OTG_HS_WKUP_IRQHandler			.weak
b .
.endm
                              
OTG_HS_IRQHandler:  
.macro OTG_HS_IRQHandler
.global  OTG_HS_IRQHandler				.weak
b .
.endm
                                                 
DCMI_IRQHandler: 
.macro DCMI_IRQHandler
.global  DCMI_IRQHandler				.weak
b .
.endm
                                                           
CRYP_IRQHandler:  
.macro CRYP_IRQHandler
.global  CRYP_IRQHandler				.weak
b .
.endm  
                                                
HASH_RNG_IRQHandler:
.macro HASH_RNG_IRQHandler
.global  HASH_RNG_IRQHandler			.weak
b .
.endm

FPU_IRQHandler:
.macro FPU_IRQHandler
.global  FPU_IRQHandler					.weak
b .
.endm

.ifdef __MICROLIB
.global  __initial_sp
.global  __heap_base
.global  __heap_limit
.else
.extern  __use_two_region_memory
.global  __user_initial_stackheap
__user_initial_stackheap:
ldr     R0, =  Heap_Mem
ldr     R1, = (Stack_Mem + Stack_Size)
ldr     R2, = (Heap_Mem +  Heap_Size)
ldr     R3, = Stack_Mem
bx      LR
.align
.endif
.end
