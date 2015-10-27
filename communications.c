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

/* SPI1CON1 レジスタの設定　*/
unsigned int S1MODE1value =
		ENABLE_SCK_PIN  &   //内臓SPIクロック有効
		ENABLE_SDO_PIN  &   //内臓モジュール（SDOピン)使用
		SPI_MODE16_ON   &   //通信単位：　16ビット
		SPI_SMP_OFF     &   //入力データを中段でサンプリングする
		SPI_CKE_OFF		&   //出力データ変化の発生：　アイドル→アクティブ変化時
		//SLAVE_ENABLE_ON		&   //SS1ピン使用する（スレーブモードのみ）
		SLAVE_ENABLE_OFF &
		CLK_POL_ACTIVE_LOW  &   //クロックの極性選択：　アイドル時Low、アクティブ時Low
		MASTER_ENABLE_ON	&   //マスターモード
		SEC_PRESCAL_2_1	    &   //２次プリスケーラ： 4：1
		PRI_PRESCAL_1_1	    ;   //１次プリスケーア： 1：1
		//SPIクロック周波数＝Fosc ×　1/4　÷（１次プリスケーラ×２次プリスケーラ）
		//　＝　32MHz×1/4÷（4×2）＝ 1MHz //なぜか，2MHzが出てたので，両方とも4:1
		//↑更にクロックを上げたため，よく分からない
		//　Ex.　4:1, 4:1　→　1MHz
		//       2:1, 1:1　→　8MHz

/*SPI2CON2 レジスタの設定 */
unsigned int S1MODE2value =
		FRAME_ENABLE_OFF	     &   //フレームSPIサポート： OFF
		FRAME_SYNC_INPUT	     &   //フレーム同期パルスを入力とする
		FRAME_POL_ACTIVE_HIGH    &   //フレーム同期パルスをアクティブHighにする
		FRAME_SYNC_EDGE_COINCIDE &   // フレーム同期パルスを最初のビットと同期する
		FIFO_BUFFER_ENABLE	     ;   //FIFOバッファー有効

/* SPI1STAT レジスタの設定 */
unsigned int S1STAvalue =
		SPI_ENABLE		&	   //SPIモジュール有効　　0xffff
		SPI_IDLE_CON	&	   //デバイスがアイドル時もモジュールは動作　　0xdfff
		SPI_RX_OVFLOW_CLR	;   //受信オーバーフローフラグビットクリア	  0xffbf

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
