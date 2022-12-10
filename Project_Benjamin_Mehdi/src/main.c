/***********************************************************************
 * 
 * Stopwatch by Timer/Counter2 on the Liquid Crystal Display (LCD)
 *
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2017 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 * Components:
 *   16x2 character LCD with parallel interface
 *     VSS  - GND (Power supply ground)
 *     VDD  - +5V (Positive power supply)
 *     Vo   - (Contrast)
 *     RS   - PB0 (Register Select: High for Data transfer, Low for Instruction transfer)
 *     RW   - GND (Read/Write signal: High for Read mode, Low for Write mode)
 *     E    - PB1 (Read/Write Enable: High for Read, falling edge writes data to LCD)
 *     D3:0 - NC (Data bits 3..0, Not Connected)
 *     D4   - PD4 (Data bit 4)
 *     D5   - PD5 (Data bit 5)
 *     D6   - PD6 (Data bit 3)
 *     D7   - PD7 (Data bit 2)
 *     A+K  - Back-light enabled/disabled by PB2
 * 
 **********************************************************************/



/*****************************************************************************************
 * Teammates: 
 *    Benjamin Della Maggiore Mahiques
 *    Mehdi Bennani
 *
 * Project : Read ADC signals from Joystick and associated push button and display 
 *           results on a LCD screen.
 * 
 * Application: give information on the direction the joystick is pointing at and the ADC 
 *              value associated. When the joystick push-button is pressed an ouput '!!!' 
 *              is displayed on the screen.
 *
 ********************************************************************************************/

//Joystick push button definition
#define JOY_PUSH PB2  


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <lcd.h>            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for number conversions

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * 
 * Purpose:  Initialize the display, set the timers/counters 1 and 2 
 *           and start the ADC conversion 
 * 
 * Returns:  none
 **********************************************************************/
int main(void)
{   
    // Initialize display
    lcd_init(LCD_DISP_ON);

    //set the pin of the joystick as a input
    GPIO_mode_input_pullup(&DDRB, JOY_PUSH);

    //position to display the value 
    lcd_gotoxy(1, 0); lcd_puts("Y:");
    lcd_gotoxy(1, 1); lcd_puts("X:");
  

    // Configure Analog-to-Digital Convertion unit
    // Select ADC voltage reference to "AVcc with external capacitor at AREF pin"
    ADMUX = ADMUX | (1<<REFS0);
    // Select input channel ADC0 (voltage divider pin)
    ADMUX = ADMUX & ~(1<<MUX3 | 1<<MUX2 | 1<<MUX1 | 1<<MUX0); //here we are clearing the four bits
    // Enable ADC module
    ADCSRA = ADCSRA | (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA = ADCSRA | (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA = ADCSRA | (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0);

    // Set the overflow prescaler to 33 ms and enable interrupt for TIM1 for the ADC conversion
    TIM1_overflow_33ms();
    TIM1_overflow_interrupt_enable();

    // Set the overflow prescaler to 4 ms and enable interrupt for TIM2 for the push-button
    TIM2_overflow_16ms();
    TIM2_overflow_interrupt_enable();


    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines, ISRs */
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/



/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Use single conversion mode and start ADC conversion every 33 ms.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    // Start ADC conversion
    ADCSRA = ADCSRA | (1<<ADSC);
}


/**********************************************************************************
 * Function: Timer/Counter2 overflow interrupt
 * Purpose: Read the push buttons' values every 16ms and display the happenening 
 *          on the LCD screen .

 *********************************************************************************/
ISR(TIMER2_OVF_vect)
{

    uint8_t Push_Joystick;

    Push_Joystick = GPIO_read(&PINB, JOY_PUSH);

     if (Push_Joystick == 0){
      lcd_clrscr();
      lcd_gotoxy(1,6);
      lcd_puts("BUZZER");
     }

}

/**********************************************************************
 * Function: ADC complete interrupt.
 * Purpose:  Read ADC value and display the direction of the joystick 
 *           depending on this value. Every time an ADC occurs the ADC
 *           channel is swapping between 1 and 0.
 **********************************************************************/
ISR(ADC_vect)
{
    uint16_t value;
    
    char string[4];  // String for converted numbers by itoa()
    static int channel = 0;
    value = ADC;

  if (channel==1){
    channel =0;
  }else{
    channel=1;
  }

    switch (channel)
    {
    case 1:
    //ADC channel 1
      ADMUX = ADMUX | 1<<MUX0;
      //display ADC for Y Axis
      itoa(value, string, 10);
      lcd_gotoxy(3,0);
      lcd_puts("    ");
      lcd_gotoxy(3,0);
      lcd_puts(string);

        if( value > 530){//the joystick is down 
        lcd_gotoxy(7, 1);
        lcd_puts("      ");
        lcd_gotoxy(7, 1);
        lcd_puts("DOWN");
    }
    if (value <530 && value>500){//the joystick is in default position 
        lcd_gotoxy(7, 1);
        lcd_puts("      ");
        lcd_gotoxy(7, 1);
        lcd_puts("CENTER");
    }
    if( value < 500){//the joystick is up
        lcd_gotoxy(7, 1);
        lcd_puts("      ");
        lcd_gotoxy(7, 1);
        lcd_puts("UP");
    }
      break;
    //ADC channel 0
    case 0:
      ADMUX = ADMUX & ~(1<<MUX3 | 1<<MUX2 | 1<<MUX1 | 1<<MUX0);
      //Display ADC value for X axis
      itoa(value, string, 10);
      lcd_gotoxy(3,1);
      lcd_puts("    ");
      lcd_gotoxy(3,1);
      lcd_puts(string);

        if( value > 520){//the joystick is on left
        lcd_gotoxy(13, 1);
        lcd_puts("      ");
        lcd_gotoxy(13, 1);
        lcd_puts("-L");
    }
    if( value < 480){//the joystick is on right
        lcd_gotoxy(13, 1);
        lcd_puts("      ");
        lcd_gotoxy(13, 1);
        lcd_puts("-R");
    }
    if ( value < 520 && value > 500){//the joystick is in the center horizontal axis
        lcd_gotoxy(13, 1);
        lcd_puts("      ");
    }
    break;
    }
}