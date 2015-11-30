
#include <stdlib.h>
#include <stdint.h>
#include "system_stm32f10x.h"

extern char __gnuld_stack_top__;
extern int main (void);

void irq_reset (void);
void irq_unused (void);

void (*irq_table[])() __attribute__((section(".irq_table"))) = 
{
  (void(*)())&__gnuld_stack_top__,       /* Initial stack pointer. */
  irq_reset,  /* Reset.                 */
  irq_unused, /* NMI.                   */
  irq_unused, /* Hardfault.             */
  irq_unused, /* MemManage.             */
  irq_unused, /* BusFault.              */
  irq_unused, /* UsageFault.            */
  NULL,       /* Reserved.              */
  NULL,       /* Reserved.              */
  NULL,       /* Reserved.              */
  irq_unused, /* SVCall.                */
  irq_unused, /* DebugMonitor.          */
  NULL,       /* Reserved.              */
  irq_unused, /* PendSV.                */
  irq_unused, /* SysTick.               */
  irq_unused, /* WWDG.                  */
  irq_unused, /* PVD.                   */
  irq_unused, /* TAMPER.                */
  irq_unused, /* RTC.                   */
  irq_unused, /* FLASH.                 */
  irq_unused, /* RCC.                   */
  irq_unused, /* EXTI0.                 */
  irq_unused, /* EXTI1.                 */
  irq_unused, /* EXTI2.                 */
  irq_unused, /* EXTI3.                 */
  irq_unused, /* EXTI4.                 */
  irq_unused, /* DMA1_Channel1.         */
  irq_unused, /* DMA1_Channel2.         */
  irq_unused, /* DMA1_Channel3.         */
  irq_unused, /* DMA1_Channel4.         */
  irq_unused, /* DMA1_Channel5.         */
  irq_unused, /* DMA1_Channel6.         */
  irq_unused, /* DMA1_Channel7.         */
  irq_unused, /* ADC1_2.                */
  irq_unused, /* CAN1_TX.               */
  irq_unused, /* CAN1_RX0.              */
  irq_unused, /* CAN1_RX1.              */
  irq_unused, /* CAN1_SCE.              */
  irq_unused, /* EXTI9_5.               */
  irq_unused, /* TIM1_BRK.              */
  irq_unused, /* TIM1_UP.               */
  irq_unused, /* TIM1_TRG_COM.          */
  irq_unused, /* TIM1_CC.               */
  irq_unused, /* TIM2.                  */
  irq_unused, /* TIM3.                  */
  irq_unused, /* TIM4.                  */
  irq_unused, /* I2C1_EV.               */
  irq_unused, /* I2C1_ER.               */
  irq_unused, /* I2C2_EV.               */
  irq_unused, /* I2C2_ER.               */
  irq_unused, /* SPI1.                  */
  irq_unused, /* SPI2.                  */
  irq_unused, /* USART1.                */
  irq_unused, /* USART2.                */
  irq_unused, /* USART3.                */
  irq_unused, /* EXTI5_10.              */
  irq_unused, /* RTCAlarm.              */
  irq_unused, /* OTG_FS_WKUP.           */
  NULL,       /* Reserved.              */
  NULL,       /* Reserved.              */
  NULL,       /* Reserved.              */
  NULL,       /* Reserved.              */
  NULL,       /* Reserved.              */
  NULL,       /* Reserved.              */
  NULL,       /* Reserved.              */
  NULL,       /* Reserved.              */
  irq_unused, /* TIM5.                  */
  irq_unused, /* SPI3.                  */
  irq_unused, /* UART4.                 */
  irq_unused, /* UART5.                 */
  irq_unused, /* TIM6.                  */
  irq_unused, /* TIM7.                  */
  irq_unused, /* DMA2_Channel1.         */
  irq_unused, /* DMA2_Channel2.         */
  irq_unused, /* DMA2_Channel3.         */
  irq_unused, /* DMA2_Channel4.         */
  irq_unused, /* DMA2_Channel5.         */
  irq_unused, /* ETH.                   */
  irq_unused, /* ETH_WKUP.              */
  irq_unused, /* CAN2_TX.               */
  irq_unused, /* CAN2_RX0.              */
  irq_unused, /* CAN2_RX1.              */
  irq_unused, /* CAN2_SCE.              */
  irq_unused, /* OTG_FS.                */
};


void __attribute__ ((naked))
 irq_reset (void)
{
  /* copy .data to RAM and init. .bss. */
  __asm__ __volatile__ (
  "ldr r13, =__gnuld_stack_top__\n\t"
  "eor r0, r0\n\t"
  "ldr r1, =__gnuld_data_load_start__\n\t"
  "ldr r2, =__gnuld_data_start__\n\t"
  "ldr r3, =__gnuld_data_size__\n\t"
  "cmp r3, r0\n\t"
  "beq _irq_reset_no_data\n\t"
  "_irq_reset_loop_data_copy:\n\t"
  "ldr r4, [r2, r0]\n\t"
  "str r4, [r1, r0]\n\t"
  "add r0, #4\n\t"
  "cmp r0, r3\n\t"
  "bge _irq_reset_loop_data_copy\n\t"
  "_irq_reset_no_data:\n\t"
  "eor r0, r0\n\t"
  "ldr r1, =__gnuld_bss_load_start__\n\t"
  "ldr r2, =__gnuld_bss_size__\n\t"
  "eor r3, r3\n\t"
  "cmp r3, r2\n\t"
  "beq _irq_reset_no_bss\n\t"
  "_irq_reset_loop_bss_init:\n\t"
  "str r3, [r1, r0]\n\t"
  "add r0, #4\n\t"
  "cmp r0, r2\n\t"
  "bge _irq_reset_loop_bss_init\n\t"
  "_irq_reset_no_bss:\n\t"
  "eor r0, r0\n\t"
  "eor r1, r1\n\t"
  "eor r2, r2\n\t"
  "eor r3, r3\n\t"
  );
  SystemInit ();
  main ();
  while (1);
}

void
 irq_unused (void)
{
  while (1);
}

