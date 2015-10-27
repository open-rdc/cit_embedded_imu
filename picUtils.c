#include "picUtils.h"


void delay_us(unsigned int N)
{
	__delay32(Clock/1900000*N);
}

//システムクロック周波数2000000HzのPICの１サイクルディレー時間＝１μsec
//　→　Clock（Hz)/2000　=　1000μsec　=　1msec　
//32000000/2000 = 160000 →　nop　×　16000回　のウェート（=　1msec）
void delay_ms(unsigned int N)   //１msec　のディレー関数
{
	__delay32(Clock/2000*N);
}

void delay_s(unsigned int N)
{
	unsigned int i;

	for(i=0 ; i<N ; i++)
	{
		delay_ms(1000);
	}
}

char intCycle_us_ErrorMsg(unsigned int limit, unsigned int N)
{
	char str[64];
	char errFlag;

	if(limit < N)
	{
		putsUART1("\r\n\r\n");
		sprintf(str, "Please be smaller than %d, the argument of intCycle_us().\r\n", limit);
		putsUART1(str);
		sprintf(str, "  Current Cycle is %d.\r\n", N);
		putsUART1(str);
		delay_ms(10000);
		errFlag = 1;
	}
	else
	{
		errFlag = 0;
	}

	return errFlag;
}

char intCycle_ms_ErrorMsg(unsigned int limit, unsigned int N)
{
	char str[64];
	char errFlag;

	if(limit < N)
	{
		putsUART1("\r\n\r\n");
		sprintf(str, "Please be smaller than %d, the argument of intCycle_ms().\r\n", limit);
		putsUART1(str);
		sprintf(str, "  Current Cycle is %d.\r\n", N);
		putsUART1(str);
		delay_ms(10000);
		errFlag = 1;
	}
	else
	{
		errFlag = 0;
	}

	return errFlag;
}

unsigned int intCycle_us_ArgmentsCheck(unsigned int N, unsigned int ps)
{
	unsigned int preScale;
	char errFlag = 0;
	switch(ps)
	{
		case T1_PS_1_1:
			preScale = 1;
			errFlag = intCycle_us_ErrorMsg(4095,N);
			break;
		case T1_PS_1_8:
			preScale = 8;
			errFlag = intCycle_us_ErrorMsg(32767,N);
			break;
		case T1_PS_1_64:
			preScale = 64;
			errFlag = intCycle_us_ErrorMsg(65535,N);
			break;
		case T1_PS_1_256:
			preScale = 256;
			errFlag = intCycle_us_ErrorMsg(65535,N);
			break;
		default:
			putsUART1("T1_PS_1_x is undefined!!!\r\n");
			delay_ms(10000);
			preScale = 1;
			break;
	}

	return preScale;
}

unsigned int intCycle_ms_ArgmentsCheck(unsigned int N, unsigned int ps)
{
	unsigned int preScale;
	char errFlag = 0;
	switch(ps)
	{
		case T1_PS_1_1:
			preScale = 1;
			errFlag = intCycle_ms_ErrorMsg(4,N);
			break;
		case T1_PS_1_8:
			preScale = 8;
			errFlag = intCycle_ms_ErrorMsg(32,N);
			break;
		case T1_PS_1_64:
			preScale = 64;
			errFlag = intCycle_ms_ErrorMsg(262,N);
			break;
		case T1_PS_1_256:
			preScale = 256;
			errFlag = intCycle_ms_ErrorMsg(1048,N);
			break;
		default:
			putsUART1("T1_PS_1_x is undefined!!!\r\n");
			delay_ms(10000);
			preScale = 1;
			break;
	}

	return preScale;
}

unsigned int intCycle_us(unsigned int N, unsigned int ps)
{
	float preScale;
	float cycleBase;

	preScale = intCycle_us_ArgmentsCheck(N, ps);

	cycleBase = (32.0 / 2.0) / preScale;

	return (unsigned int)(N*cycleBase - 1);
}

unsigned int intCycle_ms(unsigned int N, unsigned int ps)
{
	float preScale;
	float cycleBase;

	preScale = intCycle_ms_ArgmentsCheck(N, ps);

	cycleBase = 1000.0 * (32.0 / 2.0) / preScale;

	return (unsigned int)(N*cycleBase - 1);
}

void myOpenTimer1_us(unsigned int config, unsigned int ps, unsigned int cycle)
{
	OpenTimer1(config&ps, intCycle_us(cycle, ps));
}

void myOpenTimer1_ms(unsigned int config, unsigned int ps, unsigned int cycle)
{
	OpenTimer1(config&ps, intCycle_ms(cycle, ps));
}