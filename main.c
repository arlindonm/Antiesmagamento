 /**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC12F1840
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */
#define TH_HI 120
#define TH_LO 60
#define HOLDDELAY 0

//80
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    int adc,cntHi=0,cntLo=0,cntHold=0,flagFirst=0,cntBlink=0;
    int CNT_LIM_HI=50,CNT_LIM_LO=50,val=0;
	LATAbits.LATA0 = 0;
    while (1)
    {
        adc = ADC_GetConversion(3);
        if(adc>TH_HI)
               cntHi++;
        else
             cntHi=0;
        if(adc<TH_LO)
                cntLo++;
        else
             cntLo=0;
        
        if(cntHi>CNT_LIM_HI)
        {
            if(cntHold>HOLDDELAY)
                LATAbits.LATA0 = 0;
            EPWM_LoadDutyValue((adc-TH_HI+5)>>1);
			cntHi = CNT_LIM_HI;
            cntLo=0;
            flagFirst=1;
        }
        else if(cntLo>CNT_LIM_LO)
        {
            EPWM_LoadDutyValue(0);
            LATAbits.LATA0 = 1;
			cntLo = CNT_LIM_LO;
            cntHi =0;
            if(flagFirst)
                flagFirst=cntHold =0;
        }
        if(cntHold<1000)
                cntHold++;
       DAC_SetOutput(19); 
       if(CMP1_GetOutputStatus())
       {
           //CNT_LIM_LO = CNT_LIM_HI =1000;
           cntHold=1000;
           cntHi=cntLo=0;
           /*cntBlink++;
           if(cntBlink>100)
           {    
               if(val==0)val=255;
               else val =0;
               cntBlink=0;
           }
               EPWM_LoadDutyValue(val);*/
       }
       for(int i=0;i<10;i++); //delay     
       LATAbits.LATA2 = 1; 
       for(int i=0;i<4;i++);//delay
       LATAbits.LATA2 = 0; 
       for(int i=0;i<10;i++);//delay                    
    }
}
/**
 End of File
*/
