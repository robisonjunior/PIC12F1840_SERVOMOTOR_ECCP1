/**
 * ECCP Generated Driver API Header File.
 * 
 * @file eccp.h
 * 
 * @defgroup compare1 COMPARE1
 * 
 * @brief This file contains the API prototypes and other data types for the ECCP module.
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

#ifndef ECCP_H
#define ECCP_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>


/**
 * @ingroup compare1
 * @union CCPR1_PERIOD_REG_T
 * @brief Custom data type to hold the low byte, high byte and 16-bit values of the Period register.
 */
typedef union CCPR1Reg_tag
{
   struct
   {
      uint8_t ccpr1l;
      uint8_t ccpr1h;
   };
   struct
   {
      uint16_t ccpr1_16Bit;
   };
} CCPR1_PERIOD_REG_T ;

/**
 * @ingroup compare1
 * @brief Initializes the ECCP module. This is called only once before calling other ECCP APIs.
 * @param None.
 * @return None.
 */
void ECCP_Initialize(void);

/**
 * @ingroup compare1
 * @brief Sets the 16-bit compare value.
 * @pre ECCP_Initialize() is already called.
 * @param compareCount - 16-bit unsigned value
 * @return None.
 */
void ECCP_SetCompareCount(uint16_t compareCount);

/**
 * @ingroup compare1
 * @brief Implements the Interrupt Service Routine (ISR) for the compare interrupt.
 * @param None.
 * @return None.
 */
void ECCP_CompareISR(void);

#endif //ECCP_H
/**
 End of File
*/