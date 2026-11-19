/**
 * ECCP Generated Driver File.
 * 
 * @file eccp.c
 * 
 * @ingroup compare1
 * 
 * @brief This file contains the API implementation for the ECCP driver.
 *
 * @version ECCP Driver Version 1.0.0
*/
/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <xc.h>
#include "../eccp.h"

#define PULSO_0_GRAUS    830    // 830 us (ajuste fino para 0°)
#define PULSO_180_GRAUS  2250   // 2250 us (ajuste fino para 180°)
#define PERIODO_20MS     20000  // 20.000 us = 50 Hz

volatile uint16_t largura_pulso = PULSO_0_GRAUS;

void ECCP_Initialize(void)
{
    // Set the ECCP to the options selected in the User Interface

    // CCPM Output Polarity Non-Inverted; DCB 0; PM single; 
    CCP1CON = 0x8;
    
    // CCPRH 0; 
    CCPR1H = 0x0;
    
    // CCPRL 0; 
    CCPR1L = 0x0;
    
    // Clear the ECCP interrupt flag
    PIR1bits.CCP1IF = 0;
    
    // Enable the ECCP interrupt
    PIE1bits.CCP1IE = 1;
}

void ECCP_SetCompareCount(uint16_t compareCount)
{
    CCPR1_PERIOD_REG_T module;
    
    // Write the 16-bit compare value
    module.ccpr1_16Bit = compareCount;
    
    CCPR1L = module.ccpr1l;
    CCPR1H = module.ccpr1h;
}

void ECCP_CompareISR(void)
{
    // Clear the ECCP interrupt flag
    PIR1bits.CCP1IF = 0;
    
    // Add user code here
    if (CCP1CON == 0x08) {
        // O pino RA2 acabou de SUBIR -> programa descida após 'largura_pulso' us
        ECCP_SetCompareCount(CCPR1 + largura_pulso);
        CCP1CON = 0x09; // Clear output on match
    } else {
        // O pino RA2 acabou de DESCER -> programa subida no fim dos 20 ms
        ECCP_SetCompareCount(CCPR1 + (PERIODO_20MS - largura_pulso));
        CCP1CON = 0x08; // Set output on match
    }
}

/**
 End of File
*/
