#include "communications.h"

unsigned int U1MODEvalue = 
	UART_EN &
	UART_IDLE_CON &
	UART_IrDA_DISABLE &
	UART_MODE_SIMPLEX &
	UART_UEN_00 &
	UART_DIS_WAKE &
	UART_DIS_LOOPBACK &
	UART_DIS_ABAUD &
	UART_UXRX_IDLE_ONE &
	UART_BRGH_SIXTEEN &
	UART_NO_PAR_8BIT &
	UART_1STOPBIT;

unsigned int U1STAvalue =
	UART_INT_TX &
	UART_IrDA_POL_INV_ZERO &
	UART_SYNC_BREAK_DISABLED &
	UART_TX_ENABLE &
	UART_INT_RX_CHAR &
	UART_ADR_DETECT_DIS &
	UART_RX_OVERRUN_CLEAR;

/* SPI1CON1 ���W�X�^�̐ݒ�@*/
unsigned int S1MODE1value =
		ENABLE_SCK_PIN  &   //����SPI�N���b�N�L��
		ENABLE_SDO_PIN  &   //�������W���[���iSDO�s��)�g�p
		SPI_MODE16_ON   &   //�ʐM�P�ʁF�@16�r�b�g
		SPI_SMP_OFF     &   //���̓f�[�^�𒆒i�ŃT���v�����O����
		SPI_CKE_OFF		&   //�o�̓f�[�^�ω��̔����F�@�A�C�h�����A�N�e�B�u�ω���
		//SLAVE_ENABLE_ON		&   //SS1�s���g�p����i�X���[�u���[�h�̂݁j
		SLAVE_ENABLE_OFF &
		CLK_POL_ACTIVE_LOW  &   //�N���b�N�̋ɐ��I���F�@�A�C�h����Low�A�A�N�e�B�u��Low
		MASTER_ENABLE_ON	&   //�}�X�^�[���[�h
		SEC_PRESCAL_2_1	    &   //�Q���v���X�P�[���F 4�F1
		PRI_PRESCAL_1_1	    ;   //�P���v���X�P�[�A�F 1�F1
		//SPI�N���b�N���g����Fosc �~�@1/4�@���i�P���v���X�P�[���~�Q���v���X�P�[���j
		//�@���@32MHz�~1/4���i4�~2�j�� 1MHz //�Ȃ����C2MHz���o�Ă��̂ŁC�����Ƃ�4:1
		//���X�ɃN���b�N���グ�����߁C�悭������Ȃ�
		//�@Ex.�@4:1, 4:1�@���@1MHz
		//       2:1, 1:1�@���@8MHz

/*SPI2CON2 ���W�X�^�̐ݒ� */
unsigned int S1MODE2value =
		FRAME_ENABLE_OFF	     &   //�t���[��SPI�T�|�[�g�F OFF
		FRAME_SYNC_INPUT	     &   //�t���[�������p���X����͂Ƃ���
		FRAME_POL_ACTIVE_HIGH    &   //�t���[�������p���X���A�N�e�B�uHigh�ɂ���
		FRAME_SYNC_EDGE_COINCIDE &   // �t���[�������p���X���ŏ��̃r�b�g�Ɠ�������
		FIFO_BUFFER_ENABLE	     ;   //FIFO�o�b�t�@�[�L��

/* SPI1STAT ���W�X�^�̐ݒ� */
unsigned int S1STAvalue =
		SPI_ENABLE		&	   //SPI���W���[���L���@�@0xffff
		SPI_IDLE_CON	&	   //�f�o�C�X���A�C�h���������W���[���͓���@�@0xdfff
		SPI_RX_OVFLOW_CLR	;   //��M�I�[�o�[�t���[�t���O�r�b�g�N���A	  0xffbf

// BRG = ( fcy / (16*baudrate) ) - 1
unsigned int baud = 8;
/*
 * 9615:	103
 * 125000:	7
 * 1000000:	0
 */


void initUART(void)
{
	// for UART1
	RPINR18bits.U1RXR = 16;	// RX to RP16
	RPOR8bits.RP17R = 3;	// TX to RP17
	
	OpenUART1(U1MODEvalue, U1STAvalue, baud);
}

void initSPI(void)
{
	// for SPI1
	//RPOR0bits.RP0R = 	9;	//!SS:	RB0
	RPOR0bits.RP1R = 	8;	//SCLK:	RB1
	RPOR1bits.RP2R = 7;		//MISO:	RB2
	RPINR20bits.SDI1R = 3;	//MOSI:	RB3

	OpenSPI1(S1MODE1value, S1MODE2value, S1STAvalue); 
}

WORD spi_rw(WORD send)
{
	WORD recv;

	LATBbits.LATB0 = 0;
	WriteSPI1(send);
	delay_us(1);
	LATBbits.LATB0 = 1;

	delay_us(1);

	recv = ReadSPI1();

	return recv;
}
/*
void rebootUSART(void)
{
	RCSTAbits.CREN = 0;
	RCSTAbits.CREN = 1;
}

void checkAndRecover_USART(void)
{
	if(USART_Status.OVERRUN_ERROR==1)
	{	rebootUSART();	}
}
*/
