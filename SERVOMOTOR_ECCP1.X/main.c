 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
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
#include "mcc_generated_files/system/system.h"

#define PULSO_0_GRAUS    830    // 830 us (ajuste fino para 0°)
#define PULSO_180_GRAUS  2250   // 2250 us (ajuste fino para 180°)

// Usa a mesma variável que foi declarada no arquivo eccp.c
extern volatile uint16_t largura_pulso;

int main(void)
{
    SYSTEM_Initialize();

    // Configura o primeiro evento de subida do pulso em 1000 us
    ECCP_SetCompareCount(1000);
    CCP1CON = 0x08; // Set output on match

    // Habilita as interrupções Periféricas e Globais
    INTERRUPT_PeripheralInterruptEnable();
    INTERRUPT_GlobalInterruptEnable();

    // Inicia a contagem do Timer1 (1 tick = 1 us)
    TMR1_Start();

    uint8_t posicao_servo = 0; // Inicia em 0°

    while (1)
    {
        // Leitura do botão no pino RA4 (Pull-Up ativo: pressionado = 0)
        if (IO_RA4_GetValue() == 0)
        {
            __delay_ms(40); // Debounce
            if (IO_RA4_GetValue() == 0)
            {
                posicao_servo = !posicao_servo;

                // Atualiza a largura do pulso de forma segura
                PIE1bits.CCP1IE = 0;
                largura_pulso = (posicao_servo == 1) ? PULSO_180_GRAUS : PULSO_0_GRAUS;
                PIE1bits.CCP1IE = 1;

                // Aguarda soltar o botão
                while (IO_RA4_GetValue() == 0);
            }
        }
    }
}
