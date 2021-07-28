/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
 * 
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F15325
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

/*variables*/
/*ADC*/
uint16_t ADC_RES_pcbtype; //pcb type adc reading result
uint16_t ADC_RES_dimmin; //emergency dimmer inp adc reading result

uint16_t i;


/*functions prototypes*/

void AdcRead(void);



/*1ms timer*/
void T0_IH(void){
PIR0bits.TMR0IF = 0;




};

/*100ms timer*/
void T2_IH(void){
 PIR4bits.TMR2IF = 0;
AdcRead();
 IO_RA2_Toggle();


};




void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    TMR0_SetInterruptHandler(T0_IH);
    TMR2_SetInterruptHandler(T2_IH);            
    TMR0_StartTimer();
    TMR2_StartTimer();
    
    while (1)
    {
        // Add your application code
    }
}



void AdcRead(void)
{

    /*PCB type reading start*/
    ADC_Initialize();
    ADC_SelectChannel(channel_ANA4);
    ADC_StartConversion();
    while(ADC_IsConversionDone());
    ADC_RES_pcbtype = ADC_GetConversionResult();
    /*PCB type reading end*/
    
    /*Emergency dimmer input*/
    ADC_SelectChannel(channel_ANA5);
    ADC_StartConversion();
    while(ADC_IsConversionDone());
    ADC_RES_dimmin = ADC_GetConversionResult();    
    
};

/**
 End of File
*/