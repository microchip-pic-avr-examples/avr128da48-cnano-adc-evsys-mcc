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
#include <stdbool.h>

volatile bool sharedAdcFlag = false;
volatile uint16_t sharedAdcValue = 0;
uint16_t adcValue = 0;

/* macro defined to toggle the on-board LED */
#define LED_Toggle() PORTC.OUTTGL = PIN6_bm

/*
    Main application
*/
int main(void)
{
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();

    /* Replace with your application code */
    while (1)
    {
        /* if an ADC conversion has ended and the flag was set */
	   if(sharedAdcFlag == 1)
        {
            /* atomic read of the ADC conversion result */
            DISABLE_INTERRUPTS();
            adcValue = sharedAdcValue;
            ENABLE_INTERRUPTS();

            /* the LED on PC6 is toggled to visualize the end of the conversion cycle */
            LED_Toggle();

            /* printing both the raw and computed results */
            printf("ADC Conversion Raw Result = %d\r\n", adcValue);
            printf("ADC Conversion Result [V] = %.2fV\r\n", adcValue / 4096.0 * 3.3);

            /* clearing the flag */
            sharedAdcFlag = false;
        }
    }
}
/**
    End of File
*/