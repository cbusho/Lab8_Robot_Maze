/*
 * Robot_Sensors.c
 *
 *  Created on: Dec 3, 2013
 *      Author: C15Colin.Busho
 */

#include <msp430.h>
#include "Robot_Sensors.h"

void initSensors()
{
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE; // ADC10ON, interrupt enabled
	ADC10CTL1 |= ADC10SSEL1|ADC10SSEL0;                // Select SMCLK
}

unsigned int checkLeftSensor()
{
	ADC10CTL0 &= ~ENC;
	ADC10CTL1 = INCH_4;
	 ADC10AE0 |= BIT4;
	 ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	 __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
	 return ADC10MEM;
}

unsigned int checkRightSensor()
{
	 ADC10CTL0 &= ~ENC;
	 ADC10CTL1 = INCH_5;
	 ADC10AE0 |= BIT5;
	 ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	 __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
	 return ADC10MEM;
}

unsigned int checkCenterSensor()
{
	 ADC10CTL0 &= ~ENC;
	 ADC10CTL1 = INCH_3;
	 ADC10AE0 |= BIT3;
	 ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
	 __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
	 return ADC10MEM;
}

// ADC10 interrupt service routine
  #pragma vector=ADC10_VECTOR
  __interrupt void ADC10_ISR(void)
  {
    __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
  }
