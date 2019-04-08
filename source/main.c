//###########################################################################
// released by Bennyziio / 2019.04.08
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#define FLASH_program		1	// 1 = Flash Download, 0 = RAM Control

// Prototype statements for functions found within this file.
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);

Uint16 FLAG_1ms = 0;
Uint16 FLAG_500ms = 0;

Uint16 uCount_001ms = 0;
Uint16 uCount_500ms = 0;

Uint16 Watch_FLAG_1ms_Status = 0;
Uint16 Watch_FLAG_500ms_Status = 0;

float32 Cpu_Clk;
float32 Timer_Period;

void main(void)
{
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
   InitGpio();  // Skipped for this example

	#if FLASH_program
	   MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	#endif

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.TINT0 = &cpu_timer0_isr;
   PieVectTable.XINT13 = &cpu_timer1_isr;
   PieVectTable.TINT2 = &cpu_timer2_isr;

   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize the Device Peripheral. This function can be
//         found in DSP2833x_CpuTimers.c
   InitCpuTimers();   // For this example, only initialize the Cpu Timers

#if (CPU_FRQ_150MHZ)
// Configure CPU-Timer 0, 1, and 2 to interrupt every second:
// 150MHz CPU Freq, 1 second Period (in uSeconds)

   Cpu_Clk = 150;
   Timer_Period = 100;

   ConfigCpuTimer(&CpuTimer0, Cpu_Clk, Timer_Period);
   ConfigCpuTimer(&CpuTimer1, 150, 1000000);
   ConfigCpuTimer(&CpuTimer2, 150, 1000000);
#endif

//#if (CPU_FRQ_100MHZ)
//// Configure CPU-Timer 0, 1, and 2 to interrupt every second:
//// 100MHz CPU Freq, 1 second Period (in uSeconds)
//
//   ConfigCpuTimer(&CpuTimer0, 100, 1000000);
//   ConfigCpuTimer(&CpuTimer1, 100, 1000000);
//   ConfigCpuTimer(&CpuTimer2, 100, 1000000);
//#endif
// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in DSP2833x_CpuTimers.h), the
// below settings must also be updated.

   CpuTimer0Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0
   CpuTimer1Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0
   CpuTimer2Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0

// Step 5. User specific code, enable interrupts:
/************************************************************/
/* Step 5. User specific code, enable interrupts:           */
/* Copy time critical code and Flash setup code to RAM      */
/* The  RamfuncsLoadStart, RamfuncsLoadEnd,                 */
/* and RamfuncsRunStart symbols are created by the linker.  */
/* Refer to the F28335.cmd file.                            */
/************************************************************/
//MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

/************************************************************/
/* This function must reside in RAM                         */
/************************************************************/
   InitFlash();

// Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
// which is connected to CPU-Timer 1, and CPU int 14, which is connected
// to CPU-Timer 2:
   IER |= M_INT1;
   IER |= M_INT13;
   IER |= M_INT14;

// Enable TINT0 in the PIE: Group 1 interrupt 7
   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;

// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM

// Step 6. IDLE loop. Just sit and loop forever (optional):
   while(1) {
	   if(FLAG_1ms == 1) {
		   FLAG_1ms = 0;
		   GpioDataRegs.GPATOGGLE.all = 0x0000A000;
	   }
	   if(FLAG_500ms == 1) {
		   FLAG_500ms = 0;
		   GpioDataRegs.GPATOGGLE.all = 0x00004000;
	   }
   }
}

//void delay_loop() {
//	volatile long i;
//	for(i=0; i<5000000; i++) {}
//}

//__interrupt void cpu_timer0_isr(void)
//{
//   CpuTimer0.InterruptCount++;
//
////   GpioDataRegs.GPATOGGLE.all = 0xFFFFFFFF;
//   FLAG_1ms = 1;
//   Watch_FLAG_Status++;
//
//   // Acknowledge this interrupt to receive more interrupts from group 1
//   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
//}

__interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;

   if(uCount_001ms == 0) {
	   uCount_001ms = 9;
	   FLAG_1ms = 1;
	   Watch_FLAG_1ms_Status++;
   }
   else {
	   uCount_001ms--;
   }
   if(uCount_500ms == 0) {
	   uCount_500ms = 4999;
	   FLAG_500ms = 1;
	   Watch_FLAG_500ms_Status++;
   }
   else {
	   uCount_500ms--;
   }

   // Acknowledge this interrupt to receive more interrupts from group 1
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void cpu_timer1_isr(void)
{
   CpuTimer1.InterruptCount++;
   // The CPU acknowledges the interrupt.
   EDIS;
}

__interrupt void cpu_timer2_isr(void)
{  EALLOW;
   CpuTimer2.InterruptCount++;
   // The CPU acknowledges the interrupt.
   EDIS;
}

//===========================================================================
// No more.
//===========================================================================
