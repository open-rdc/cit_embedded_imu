#ifndef _PICUTILS_H_
#define _PICUTILS_H_

#include "p24FJ64GA004.h"
#include <stdio.h>
#include <stdlib.h>
#include <timer.h>
#include <uart.h>

#define Clock   32000000	// ’PˆÊ‚ÍHz‚ÅŽw’è

void delay_us(unsigned int N);
void delay_ms(unsigned int N);
void delay_s(unsigned int N);
unsigned int intCycle_us(unsigned int N, unsigned int ps);
unsigned int intCycle_ms(unsigned int N, unsigned int ps);

void myOpenTimer1_us(unsigned int config, unsigned int ps, unsigned int cycle);
void myOpenTimer1_ms(unsigned int config, unsigned int ps, unsigned int cycle);
void myOpenTimer2_us(unsigned int config, unsigned int ps, unsigned int cycle);

#endif
