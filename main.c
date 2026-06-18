#include <xc.h>
#define _XTAL_FREQ 20000000
###
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

void PWM_Init(void) {
    TRISCbits.TRISC2 = 0;
    CCP1CON = 0x0C;
    PR2 = 255;
    T2CON = 0x06;
    CCPR1L = 0;
}

void main(void) {
    unsigned int time_taken;
    unsigned int timeout;
    int distance;

    TRISDbits.TRISD0 = 0;
    TRISCbits.TRISC0 = 0;   // TRIG
    TRISCbits.TRISC1 = 1;   // ECHO
    TRISCbits.TRISC2 = 0;   // BUZZER

    PORTDbits.RD0 = 0;
    PORTCbits.RC0 = 0;

    T1CON = 0x30;
    PWM_Init();

    while(1) {
        TMR1H = 0;
        TMR1L = 0;

        PORTCbits.RC0 = 1;
        __delay_us(10);
        PORTCbits.RC0 = 0;

        timeout = 0;
        while(PORTCbits.RC1 == 0 && timeout < 30000) {
            timeout++;
        }

        if(timeout >= 30000) {
            PORTDbits.RD0 = 0;
            CCPR1L = 0;
            __delay_ms(100);
            continue;
        }

        T1CONbits.TMR1ON = 1;

        timeout = 0;
        while(PORTCbits.RC1 == 1 && timeout < 60000) {
            timeout++;
        }

        T1CONbits.TMR1ON = 0;

        if(timeout >= 60000) {
            PORTDbits.RD0 = 0;
            CCPR1L = 0;
            __delay_ms(100);
            continue;
        }

        time_taken = ((unsigned int)TMR1H << 8) | TMR1L;
        distance = time_taken / 36;

        if(distance > 0 && distance <= 10) {
            PORTDbits.RD0 = 1;
            CCPR1L = 128;
        }
        else if(distance > 10 && distance <= 20) {
            PORTDbits.RD0 = 1;
            CCPR1L = 128;
            __delay_ms(80);

            CCPR1L = 0;
            PORTDbits.RD0 = 0;
            __delay_ms(120);
        }
        else {
            PORTDbits.RD0 = 0;
            CCPR1L = 0;
        }

        __delay_ms(50);
    }
}
