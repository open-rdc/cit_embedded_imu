#ifndef __COMMUNICATIONS_H__
#define __COMMUNICATIONS_H__
#include "p24FJ64GA004.h"
#include <spi.h>
#include <uart.h>
#include "types.h"
#include "picUtils.h"


void initUART(void);
void initSPI(void);

WORD spi_rw(WORD send);
//void checkAndRecover_USART(void);

#endif
