#include "bitOperation.h"

void bitStreamInverse_16(WORD* data)
{
	int i=0;
	WORD temp = 0;
	for(i=0 ; i<16 ; i++)
	{
		temp += ((*data>>i) & 0x0001) << (15-i);
	}
	*data = temp;
}

void bitStreamInverse_32(DWORD* data)
{
	int i=0;
	DWORD temp = 0;
	for(i=0 ; i<32 ; i++)
	{
		temp += ((*data>>i) & 0x00000001) << (31-i);
	}
	*data = temp;
}

BYTE wordLow(WORD arg)
{
	return (BYTE)(arg & 0x00FF);
}

BYTE wordHigh(WORD arg)
{
	return (BYTE)((arg>>8) & 0x00FF);
}

WORD dwordLow(DWORD arg)
{
	return (WORD)(arg & 0x0000FFFF);
}

WORD dwordHigh(DWORD arg)
{
	return (WORD)((arg>>16) & 0x0000FFFF);
}


WORD byte2word(BYTE h, BYTE l)
{
	return (WORD)((WORD)(((WORD)h<<8)&0xFF00) | (WORD)l);
}

DWORD word2dword(WORD h, WORD l)
{
	return (DWORD)((DWORD)(((DWORD)h<<16)&0xFFFF0000) | (DWORD)l);
}

