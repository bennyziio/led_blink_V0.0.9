//###########################################################################
//
// FILE:	DSP2833x_Gpio.c
//
// TITLE:	DSP2833x General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V142 $
// $Release Date: November  1, 2016 $
// $Copyright: Copyright (C) 2007-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

//
// Included Files
//
#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

//
// InitGpio - This function initializes the Gpio to a known (default) state.
//
// For more details on configuring GPIO's as peripheral functions,
// refer to the individual peripheral examples and/or GPIO setup example. 
//
void 
InitGpio(void)
{
	// MUX = 0,0 : GPIO
	//     = 0,1 : PER1
	//     = 1.0 : PER2
	//     = 1,1 : PER3
	// PUD = 0 : pullup
	//	   = 1 : no - pullup
	// DIR : 0 = INPUT, 1 = OUTPUT

    EALLOW;
    // [ AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA ]
    GpioCtrlRegs.GPAMUX2.all = 0x05550FA0;     	// GPIO functionality GPIO16-GPIO31
    GpioCtrlRegs.GPAMUX1.all = 0x00000000;     	// GPIO functionality GPIO0-GPIO15

    //GpioCtrlRegs.GPAQSEL1.all = 0x0000;    	// GPIO0-GPIO15 Synch to SYSCLKOUT
	//GpioCtrlRegs.GPAQSEL2.all = 0x0000;    	// GPIO16-GPIO31 Synch to SYSCLKOUT

    GpioCtrlRegs.GPAPUD.all = 0x0000;      		// Pullup's enabled GPIO0-GPIO31

    GpioCtrlRegs.GPADIR.all = 0xE0D6FFFF;      	// GPIO0-GPIO31 out direction
    GpioDataRegs.GPADAT.all	= 0xE0D6FFFF;	// Out Data
    //GpioDataRegs.GPASET.all = 0xE0D6FFFF;		// Set High
	//GpioDataRegs.GPACLEAR.all = 0x1F250000;		// Set Low

    /* GPIO_NUM	= GPAMUX2 	: GPAPUD 	: FUNC 		: 	GPADIR 	  :  GPADAT : DISCRIPTION
    	GPIOB31 = 00		:	0		: GPIO 		: 	OUTPUT	1 : 	1 	: not used
    	GPIOB30 = 00		:	0		: GPIO 		: 	OUTPUT  1 : 	1 	: not used
    	GPIOB29 = 01		:	0		: SCITXDA 	: 	OUTPUT 	1 : 	1 	: TXD_A
    	GPIOB28 = 01		:	0		: SCIRXDA 	: 	INPUT  	0 : 	0 	: RXD_A

    	GPIOB27 = 01		:	0		: ECAP4 	: 	INPUT  	0 : 	0 	: FB_RWST_B
    	GPIOB26 = 01		:	0		: ECAP3 	: 	INPUT  	0 : 	0 	: FB_RWST_A
    	GPIOB25 = 01		:	0		: ECAP2 	: 	INPUT  	0 : 	0 	: FB_LWST_B
    	GPIOB24 = 01		:	0		: ECAP1 	: 	INPUT  	0 : 	0 	: FB_LWST_A

    	GPIOB23 = 00		:	0		: GPIO 		: 	INPUT   1 : 	1 	: not used
    	GPIOB22 = 00		:	0		: GPIO 		: 	INPUT   1 : 	1 	: not used
    	GPIOB21 = 11		:	0		: CANRXB	: 	INPUT  	0 : 	0 	: CANRXB
    	GPIOB20 = 11		:	0		: CANTXB	: 	OUTPUT 	1 : 	1 	: CANTXB

    	GPIOB19 = 10		:	0		: SCIRXDB	: 	INPUT  	0 : 	0 	: SCI_RXB
    	GPIOB18 = 10		:	0		: SCITXDB	: 	OUTPUT 	1 : 	1 	: SCI_TXB
    	GPIOB17 = 00		:	0		: GPIO 		: 	OUTPUT  1 : 	1 	: not used
    	GPIOB16 = 00		:	0		: GPIO 		: 	INPUT   0 : 	0 	: not used

      GPIO_NUM	= GPAMUX1
    	GPIOB15	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: LED3
    	GPIOB14	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: LED2
    	GPIOB13	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1	: LED1
    	GPIOB12	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: EN_PBIT_CHECK2

    	GPIOB11	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: EN_PBIT_CHECK1
    	GPIOB10	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: DO_PBIT
    	GPIOB9	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: DO_PBIT_STAT
    	GPIOB8	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: DO_LIFE_PULSE

    	GPIOB7	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: IF_LDACn
    	GPIOB6	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: IF_RESETn
    	GPIOB5	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: IF_nHOLDC
    	GPIOB4	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: IF_nHOLDB

    	GPIOB3	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: IF_nHOLDA
    	GPIOB2	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: EN_MS_OUTPUT
    	GPIOB1	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: CSn_RWST
    	GPIOB0	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: CSn_LWST
    */

	// [ BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB ]

    GpioCtrlRegs.GPBMUX2.all = 0x00055000;     	// GPIO functionality GPIO48-GPIO63
    GpioCtrlRegs.GPBMUX1.all = 0xFFFF3FF5;     	// GPIO functionality GPIO32-GPIO39

    GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;		// Async input GPIO32 (SDAA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;		// Async input GPIO33 (SCLA)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 3;		// Async input GPIO54 (SPISI)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 3;		// Async input GPIO55 (SPISO)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 3;		// Async input GPIO56 (SPICLK)
    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 3;		// Async input GPIO57 (SPISTE)

    GpioCtrlRegs.GPBPUD.all = 0x03000077;      	// Pullup's enabled GPIO32-GPIO63

    GpioCtrlRegs.GPBDIR.all = 0x0380FFFF;      	// GPIO32-GPIO63 out direction

    GpioDataRegs.GPBDAT.all = 0x020000F7;		// Out data

    /* GPIO_NUM	= GPBMUX2 	: GPBPUD 	: FUNC 		: 	GPBDIR 	  :  GPBDAT : DISCRIPTION
		GPIOB63 = 00		:	0		: GPIO 		: 	INPUT	0 : 	0 	: not used
		GPIOB62 = 00		:	0		: GPIO 		: 	INPUT  	0 : 	0 	: not used
		GPIOB61 = 00		:	0		: GPIO 		: 	INPUT 	0 : 	0 	: not used
		GPIOB60 = 00		:	0		: GPIO 		: 	INPUT  	0 : 	0 	: not used

		GPIOB59 = 00		:	0		: GPIO 		: 	INPUT  	0 : 	0 	: not used
		GPIOB58 = 00		:	0		: GPIO 		: 	INPUT  	0 : 	0 	: not used
		GPIOB57 = 01		:	1		: SPISTE 	: 	OUTPUT  1 : 	1 	: SPISTE A
		GPIOB56 = 01		:	1		: SPICLK 	: 	OUTPUT  1 : 	0 	: SPICLK A

		GPIOB55 = 01		:	0		: SPISO 	: 	OUTPUT  1 : 	0 	: SPISOMI A
		GPIOB54 = 01		:	0		: SPISI 	: 	INPUT   0 : 	0 	: SPISIMO A
		GPIOB53 = 00		:	0		: GPIO		: 	INPUT  	0 : 	0 	: not used
		GPIOB52 = 00		:	0		: GPIO		: 	INPUT 	0 : 	0 	: not used

		GPIOB51 = 00		:	0		: GPIO		: 	INPUT  	0 : 	0 	: not used
		GPIOB50 = 00		:	0		: GPIO		: 	INPUT 	0 : 	0 	: not used
		GPIOB49 = 00		:	0		: GPIO 		: 	INPUT  	0 : 	0 	: not used
		GPIOB48 = 00		:	0		: GPIO 		: 	INPUT   0 : 	0 	: not used

	  GPIO_NUM	= GPBMUX1
		GPIOB47	= 11		:	0		: XA7 		: 	OUTPUT 	1 : 	0 	: XA7
		GPIOB46	= 11		:	0		: XA6 		: 	OUTPUT 	1 : 	0 	: XA6
		GPIOB45	= 11		:	0		: XA5 		: 	OUTPUT 	1 : 	0	: XA5
		GPIOB44	= 11		:	0		: XA4 		: 	OUTPUT 	1 : 	0 	: XA4

		GPIOB43	= 11		:	0		: XA3 		: 	OUTPUT 	1 : 	0 	: XA3
		GPIOB42	= 11		:	0		: XA2 		: 	OUTPUT 	1 : 	0 	: XA2
		GPIOB41	= 11		:	0		: XA1 		: 	OUTPUT 	1 : 	0 	: XA1
		GPIOB40	= 11		:	0		: XA0 		: 	OUTPUT 	1 : 	0 	: XA0

		GPIOB39	= 00		:	0		: GPIO 		: 	OUTPUT 	1 : 	1 	: not used
		GPIOB38	= 11		:	1		: WE0 		: 	OUTPUT 	1 : 	1 	: WE0
		GPIOB37	= 11		:	1		: CS7 		: 	OUTPUT 	1 : 	1 	: nCS7
		GPIOB36 = 11		:	1		: CS0 		: 	OUTPUT 	1 : 	1 	: nCS0

		GPIOB35	= 11		:	0		: XRnW 		: 	OUTPUT 	1 : 	0 	: XRnW
		GPIOB34	= 11		:	1		: XREADY 	: 	OUTPUT 	1 : 	1 	: READY
		GPIOB33	= 01		:	1		: SCLA 		: 	OUTPUT 	1 : 	1 	: SCLA
		GPIOB32	= 01		:	1		: SDAA 		: 	OUTPUT 	1 : 	1 	: SDAA
	*/

    // [ CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC ]

    GpioCtrlRegs.GPCMUX2.all = 0x0000FFFF;     	// GPIO functionality GPIO80-GPIO87
    GpioCtrlRegs.GPCMUX1.all = 0xFFFFFFFF;     	// GPIO functionality GPIO64-GPIO79

    GpioCtrlRegs.GPCDIR.all = 0x00FF0000;      	// GPI064-GPIO95 out direction

    GpioCtrlRegs.GPCPUD.all = 0x00000000;      	// Pullup's enabled GPIO64-GPIO87

    GpioDataRegs.GPCDAT.all = 0x00000000;		// Out Data

    /* GPIO_NUM	= GPCMUX2 	: GPCPUD 	: FUNC 		: 	GPCDIR 	  :  GPCDAT : DISCRIPTION
		GPIOC95 = X
		GPIOC94 = X
		GPIOC93 = X
		GPIOC92 = X

		GPIOC91 = X
		GPIOC90 = X
		GPIOC89 = X
		GPIOC88 = X

		GPIOC87 = 11		:	0		: XA15	 	: 	OUTPUT  1 : 	0 	: XA15
		GPIOC86 = 11		:	0		: XA14	 	: 	OUTPUT  1 : 	0 	: XA14
		GPIOC85 = 11		:	0		: XA13		: 	OUTPUT  1 : 	0 	: XA13
		GPIOC84 = 11		:	0		: XA12		: 	OUTPUT 	1 : 	0 	: XA12

		GPIOC83 = 11		:	0		: XA11		: 	OUTPUT  1 : 	0 	: XA11
		GPIOC82 = 11		:	0		: XA10		: 	OUTPUT 	1 : 	0 	: XA10
		GPIOC81 = 11		:	0		: XA9 		: 	OUTPUT  1 : 	0 	: XA9
		GPIOC80 = 11		:	0		: XA8 		: 	OUTPUT  1 : 	0 	: XA8

	  GPIO_NUM	= GPCMUX1
		GPIOC79	= 11		:	0		: XD0 		: 	INPUT 	0 : 	0 	: XD0
		GPIOC78	= 11		:	0		: XD1 		: 	INPUT 	0 : 	0 	: XD1
		GPIOC77	= 11		:	0		: XD2 		: 	INPUT 	0 : 	0	: XD2
		GPIOC76	= 11		:	0		: XD3 		: 	INPUT 	0 : 	0 	: XD3

		GPIOC75	= 11		:	0		: XD4 		: 	INPUT 	0 : 	0 	: XD4
		GPIOC74	= 11		:	0		: XD5 		: 	INPUT 	0 : 	0 	: XD5
		GPIOC73	= 11		:	0		: XD6 		: 	INPUT 	0 : 	0	: XD6
		GPIOC72	= 11		:	0		: XD7 		: 	INPUT 	0 : 	0 	: XD7

		GPIOC71	= 11		:	0		: XD8 		: 	INPUT 	0 : 	0 	: XD8
		GPIOC70	= 11		:	0		: XD9 		: 	INPUT 	0 : 	0 	: XD9
		GPIOC69	= 11		:	0		: XD10 		: 	INPUT 	0 : 	0	: XD10
		GPIOC68	= 11		:	0		: XD11 		: 	INPUT 	0 : 	0 	: XD11

		GPIOC67	= 11		:	0		: XD12 		: 	INPUT 	0 : 	0 	: XD12
		GPIOC66	= 11		:	0		: XD13 		: 	INPUT 	0 : 	0 	: XD13
		GPIOC65	= 11		:	0		: XD14 		: 	INPUT 	0 : 	0	: XD14
		GPIOC64	= 11		:	0		: XD15 		: 	INPUT 	0 : 	0 	: XD15
	*/

    EDIS;
}	
	
//
// End of file
//

