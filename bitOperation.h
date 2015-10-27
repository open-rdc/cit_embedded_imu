#ifndef _BITOPERATION_H_
#define _BITOPERATION_H_
#include "types.h"

void bitStreamInverse_16(WORD* data);

BYTE wordLow(WORD arg);
BYTE wordHigh(WORD arg);
WORD dwordLow(DWORD arg);
WORD dwordHigh(DWORD arg);

WORD byte2word(BYTE h, BYTE l);
DWORD word2dword(WORD h, WORD l);

#endif

