#include "adisUtils.h"

axis  imu_gyro;
axis  imu_accele;
axis  imu_deltaAng;
axis  imu_deltaVel;
axis	imu_magneto;
WORD	imu_baro_w;
float	imu_baro_f;
WORD imu_temp_w;
float imu_temp_f;
axis  imu_angle;
axis  imu_velocity;
WORD   imu_firmrev;
WORD   imu_firmrev_dm;
WORD   imu_firmrev_y;
WORD   imu_diag;
DWORD imu_avg_tmp[4] = {0,0,0,0};

void imu_adisUtil_init(void)
{
	imu_clearAngle();
	imu_clearVelocity();
}


  /* sensor operation */
void imu_clearAngle(void)
{
	imu_angle.dw.x = 0;
	imu_angle.dw.y = 0;
	imu_angle.dw.z = 0;
	imu_angle.f.x = 0;
	imu_angle.f.y = 0;
	imu_angle.f.z = 0;
}

void imu_clearVelocity(void)
{
	imu_velocity.dw.x = 0;
	imu_velocity.dw.y = 0;
	imu_velocity.dw.z = 0;
	imu_velocity.f.x = 0;
	imu_velocity.f.y = 0;
	imu_velocity.f.z = 0;
}

void imu_readSensor(void)
{
	imu_getGyro();
	imu_getAccele();
//	imu_getDeltaAngle();
//	imu_getDeltaVelocity();
//	imu_getMagneto();
//	imu_getBarometer();
	imu_getTemperature();

	imu_getAngle();
//	imu_getVelocity();
}

/*
string imu_allSensorSend(void)
{
	stringstream s;
	stringstream t;
	
	t << temp << ",";
	
	s << dw2string_3axis(gyro.dw) +
		 dw2string_3axis(accele.dw) +
		 dw2string_3axis(imu_deltaAng.dw) +
		 dw2string_3axis(imu_deltaVel.dw) +
		 dw2string_3axis(imu_angle.dw) +
		 dw2string_3axis(velocity.dw) +
		 t.str();
		
	return s.str();
}
*/

void imu_allSensorSend_(char ret[15])
{
	return imu_dw2byteArray_3axis(imu_angle.dw, ret);
}

  /* Utility's */
WORD imu_getGyroScale_x(void)
{
	imu_setPage(2);
	imu_readRegister(XGYRO_SCL);
	imu_setPage(0);
}

WORD imu_getGyroScale_y(void)
{
	imu_setPage(2);
	imu_readRegister(YGYRO_SCL);
	imu_setPage(0);
}

WORD imu_getGyroScale_z(void)
{
	imu_setPage(2);
	imu_readRegister(ZGYRO_SCL);
	imu_setPage(0);
}

void imu_setGyroScale_x(WORD arg)
{
	imu_setPage(2);
	imu_writeRegister(XGYRO_SCL, arg);
	imu_setPage(0);
}

void imu_setGyroScale_y(WORD arg)
{
	imu_setPage(2);
	imu_writeRegister(YGYRO_SCL, arg);
	imu_setPage(0);
}

void imu_setGyroScale_z(WORD arg)
{
	imu_setPage(2);
	imu_writeRegister(ZGYRO_SCL, arg);
	imu_setPage(0);
}

WORD imu_getAcceleScale_x(void)
{
	imu_setPage(2);
	imu_readRegister(XACCL_SCL);
	imu_setPage(0);
}

WORD imu_getAcceleScale_y(void)
{
	imu_setPage(2);
	imu_readRegister(YACCL_SCL);
	imu_setPage(0);
}

WORD imu_getAcceleScale_z(void)
{
	imu_setPage(2);
	imu_readRegister(ZACCL_SCL);
	imu_setPage(0);
}

void imu_setAcceleScale_x(WORD arg)
{
	imu_setPage(2);
	imu_writeRegister(XACCL_SCL, arg);
	imu_setPage(0);
}

void imu_setAcceleScale_y(WORD arg)
{
	imu_setPage(2);
	imu_writeRegister(YACCL_SCL, arg);
	imu_setPage(0);
}

void imu_setAcceleScale_z(WORD arg)
{
	imu_setPage(2);
	imu_writeRegister(ZACCL_SCL, arg);
	imu_setPage(0);
}

void imu_scaleGyroIncrimental_x(int arg)
{
	WORD scale;
	if(arg < 0)	scale = (WORD)(0x8000 | (WORD)arg);
	else		scale = (WORD)arg;
	imu_setGyroScale_x( imu_getGyroScale_x() + scale );
}

void imu_scaleGyroIncrimental_y(int arg)
{
	WORD scale;
	if(arg < 0)	scale = (WORD)(0x8000 | (WORD)arg);
	else		scale = (WORD)arg;

	imu_setGyroScale_y( imu_getGyroScale_y() + scale );
}

void imu_scaleGyroIncrimental_z(int arg)
{
	WORD scale;
	if(arg < 0)	scale = (WORD)(0x8000 | (WORD)arg);
	else		scale = (WORD)arg;

	imu_setGyroScale_z( imu_getGyroScale_z() + scale );
}

void imu_scaleAcceleIncrimental_x(int arg)
{
	WORD scale;
	if(arg < 0)	scale = (WORD)(0x8000 | (WORD)arg);
	else		scale = (WORD)arg;
	imu_setAcceleScale_x( imu_getAcceleScale_x() + scale );
}

void imu_scaleAcceleIncrimental_y(int arg)
{
	WORD scale;
	if(arg < 0)	scale = (WORD)(0x8000 | (WORD)arg);
	else		scale = (WORD)arg;

	imu_setAcceleScale_y( imu_getAcceleScale_y() + scale );
}

void imu_scaleAcceleIncrimental_z(int arg)
{
	WORD scale;
	if(arg < 0)	scale = (WORD)(0x8000 | (WORD)arg);
	else		scale = (WORD)arg;

	imu_setAcceleScale_z( imu_getAcceleScale_z() + scale );
}

WORD imu_avg_dec_filter(float sps)
{
	const float internal_avg_dec_freq = 2460.0;
	
	//float max_sps = internal_avg_dec_freq / 1;
	//float min_sps = internal_avg_dec_freq / 2048;
	
	WORD dec = (WORD)(internal_avg_dec_freq / sps) - 1;

	/*
	if(sps < min_sps)
	{
		printf("#  DEC_RATE minimum error\n\r");
		sps = min_sps;
	}
	if(sps > max_sps)
	{
		printf("#  DEC_RATE maximum error\n\r");
		sps = max_sps;
	}
	*/
	
	imu_setPage(3);
	imu_writeRegister(DEC_RATE, dec);
	imu_setPage(0);
	
	return dec;
}

void imu_biasNull_setAverageTime(WORD tc, WORD bias)
{
	const WORD gyro_biasCollectionAllEnable = 0x0700;
	//const WORD accl_biasCollectionAllEnable = 0x3800;
	
	//WORD biasCollection = gyro_biasCollectionAllEnable | accl_biasCollectionAllEnable;
	
	imu_setPage(3);
	imu_writeRegister(NULL_CFG, bias | tc);
	imu_setPage(0);
}

// see biasNull_setAverageTime
void imu_biasNull(void)
{
	const WORD param = 0x0001;
	
	imu_setPage(3);
	imu_writeRegister(GLOB_CMD, param);
	imu_setPage(0);
}

// 74msec
// 120msec ADIS16488
void imu_softwareReset(void)
{
	const WORD param = 0x0080;
	
	imu_setPage(3);
	imu_writeRegister(GLOB_CMD, param);
	imu_setPage(0);
	delay_ms(140);
}

// 54msec
// 75msec ADIS16488
void imu_factoryCalibrationRestore(void)
{
	const WORD param = 0x0040;
	
	imu_setPage(3);
	imu_writeRegister(GLOB_CMD, param);
	imu_setPage(0);
        delay_ms(95);
}

// 10msec
// 12msec ADIS16488
void imu_selfTest(void)
{
	const WORD param = 0x0002;
	spi_rw(DIAG_STS);//DIAG_STS reset ˆê‰ž
	
	imu_setPage(3);
	imu_writeRegister(GLOB_CMD, param);
	delay_ms(20);
	imu_setPage(0);
	spi_rw(DIAG_STS);
	imu_diag = spi_rw(PAGE_ID);
}

// --msec
// 375msec ADIS16488
void imu_flashMemoryUpdate(void)
{
	const WORD param = 0x0008;
	
	imu_setPage(3);
	imu_writeRegister(GLOB_CMD, param);
	imu_setPage(0);
	delay_ms(400);
}

void imu_getFirmwareRevision(void)
{
	imu_setPage(3);
					spi_rw(FIRM_REV);
	imu_firmrev = 	spi_rw(FIRM_DM);
	imu_firmrev_dm =spi_rw(FIRM_Y);
	imu_firmrev_y = spi_rw(PAGE_ID);
	imu_setPage(0);
}

//--private--//
void imu_genericRead_3axis(axis_3_dw* read, unsigned int baseAddr)
{
	dw_w dw;
		   spi_rw(baseAddr);	 // set first spi data
	dw.low   = spi_rw(baseAddr + 0x0200);
	dw.high  = spi_rw(baseAddr + 0x0400);
	read->x  = word2dword(dw.high, dw.low);
	
	dw.low   = spi_rw(baseAddr + 0x0600);
	dw.high  = spi_rw(baseAddr + 0x0800);
	read->y  = word2dword(dw.high, dw.low);
	
	dw.low   = spi_rw(baseAddr + 0x0A00);
	dw.high  = spi_rw(PAGE_ID); // read spi buffer
	read->z  = word2dword(dw.high, dw.low);

}

void imu_genericIncremental_3axis(axis_3_dw* read, unsigned int baseAddr)
{
	dw_w dw;
                   spi_rw(baseAddr);	 // set first spi data
	dw.low   = spi_rw(baseAddr + 0x0200);
	dw.high  = spi_rw(baseAddr + 0x0400);
	read->x += word2dword(dw.high, dw.low);
	
	dw.low   = spi_rw(baseAddr + 0x0600);
	dw.high  = spi_rw(baseAddr + 0x0800);
	read->y += word2dword(dw.high, dw.low);
	
	dw.low   = spi_rw(baseAddr + 0x0A00);
	dw.high  = spi_rw(PAGE_ID); // read spi buffer
	read->z += word2dword(dw.high, dw.low);
}

void imu_discrete2real_w(WORD w, float* f, double unit)
{
	if(w > 0x7FFF)   *f = -(float)((0xFFFF-w) * unit);
	else			 *f =  (float)(w * unit);
}

void imu_discrete2real_dw(DWORD dw, float* f, double unit)
{
	if(dw > 0x7FFFFFFF)   *f = -(float)((0xFFFFFFFF-dw) * unit);
	else				  *f =  (float)(dw * unit);
}

void imu_discrete2real_3axis(axis_3_dw dw, axis_3_f* f, double unit)
{
	imu_discrete2real_dw(dw.x, &f->x, unit);
	imu_discrete2real_dw(dw.y, &f->y, unit);
	imu_discrete2real_dw(dw.z, &f->z, unit);
}

void imu_dw2byteArray(DWORD arg, char ret[5])
{
	ret[0] = wordLow( dwordLow(arg) );
	ret[1] = wordHigh( dwordLow(arg) );
	ret[2] = wordLow( dwordHigh(arg) );
	ret[3] = wordHigh( dwordHigh(arg) );
	ret[4] = ',';
}

void imu_dw2byteArray_3axis(axis_3_dw dw, char ret[15])
{
	imu_dw2byteArray(dw.x, &ret[0]);
	imu_dw2byteArray(dw.y, &ret[5]);
	imu_dw2byteArray(dw.z, &ret[10]);
}

/*
string dw2string_3axis(axis_3_dw dw)
{
	stringstream ss;
	
	ss << dw.x << ',' << dw.y << ',' << dw.z << ',';
	return ss.str();
}
*/

void imu_writeRegister(WORD reg, WORD arg)
{
	spi_rw(reg | (WORD)wordLow(arg));
	spi_rw((reg+0x0100) | (WORD)wordHigh(arg));
//	spi_rw((reg+0x0100));
}

WORD imu_readRegister(WORD reg)
{
	spi_rw(reg & 0x7FFF);
	return spi_rw(reg & 0x7FFF);
}

void imu_setPage(unsigned int page)
{
	spi_rw(0x8000|page);
}

void imu_check_switch_pm(void){
	if(imu_angle.f.x >= 180.0){
		imu_angle.dw.x -= 0xA82CD8C2; //180/DELTA_VEL_UNIT*2
	}else if(imu_angle.f.x < -180.0){
		imu_angle.dw.x += 0xA82CD8C2;
	}
	if(imu_angle.f.y >= 180.0){
		imu_angle.dw.y -= 0xA82CD8C2; //180/DELTA_VEL_UNIT*2
	}else if(imu_angle.f.y < -180.0){
		imu_angle.dw.y += 0xA82CD8C2;
	}
	if(imu_angle.f.z >= 180.0){
		imu_angle.dw.z -= 0xA82CD8C2; //180/DELTA_VEL_UNIT*2
	}else if(imu_angle.f.z < -180.0){
		imu_angle.dw.z += 0xA82CD8C2;
	}
}

  /*  sensor operation  */
void imu_getGyro(void)
{
	imu_genericRead_3axis(&imu_gyro.dw, BASE_GYRO);
	imu_discrete2real_3axis(imu_gyro.dw, &imu_gyro.f, GYRO_UNIT);
}

void imu_getAccele(void)
{
	imu_genericRead_3axis(&imu_accele.dw, BASE_ACCL);
	imu_discrete2real_3axis(imu_accele.dw, &imu_accele.f, ACCL_UNIT);

}

void imu_getMagneto(void)
{
			   			spi_rw(X_MAGN_OUT);	 // set first spi data
	imu_magneto.dw.x  = spi_rw(Y_MAGN_OUT);
	imu_magneto.dw.y  = spi_rw(Z_MAGN_OUT);
	imu_magneto.dw.z  = spi_rw(PAGE_ID); 	// read spi buffer
	imu_discrete2real_3axis(imu_magneto.dw, &imu_magneto.f, MAGN_UNIT);
}

void imu_getDeltaAngle(void)
{
	imu_genericRead_3axis(&imu_deltaAng.dw, BASE_DELTA_ANG);
	imu_discrete2real_3axis(imu_deltaAng.dw, &imu_deltaAng.f, DELTA_ANG_UNIT);
}

void imu_getDeltaVelocity(void)
{
	imu_genericRead_3axis(&imu_deltaVel.dw, BASE_DELTA_VEL);
	imu_discrete2real_3axis(imu_deltaVel.dw, &imu_deltaVel.f, DELTA_VEL_UNIT);
}

void imu_getBarometer(void)
{
	dw_w dw;
	DWORD w;
			  spi_rw(BAROM_LOW);	// set first spi data
	dw.low	= spi_rw(BAROM_OUT);
	dw.high	= spi_rw(PAGE_ID);		// read spi buffer
	w = word2dword(dw.high, dw.low);
	
	imu_baro_w = w;

	imu_discrete2real_dw(w, &imu_baro_f, BARO_UNIT);
}

void imu_getTemperature(void)
{
	const float baseTemp = 25.0;
	WORD w;
	
		spi_rw(TEMP_OUT);
	w = spi_rw(PAGE_ID);
	
	imu_temp_w = w;

	imu_discrete2real_w(w, &imu_temp_f, TEMP_UNIT);
	
	imu_temp_f = baseTemp + imu_temp_f;
}

void imu_getAngle(void)
{   
	imu_genericIncremental_3axis(&imu_angle.dw, BASE_DELTA_ANG);
        imu_angle.dw.y = imu_accele.dw.x;
	imu_discrete2real_3axis(imu_angle.dw, &imu_angle.f, DELTA_ANG_UNIT);
	imu_check_switch_pm();
/*
	imu_angle.f.x = (float)(imu_angle.dw.x * DELTA_ANG_UNIT);
	imu_angle.f.y = (float)(imu_angle.dw.y * DELTA_ANG_UNIT);
	imu_angle.f.z = (float)(imu_angle.dw.z * DELTA_ANG_UNIT);
*/
}

void imu_getVelocity(void)
{   
	imu_genericIncremental_3axis(&imu_velocity.dw, BASE_DELTA_VEL);
	imu_discrete2real_3axis(imu_velocity.dw, &imu_velocity.f, DELTA_VEL_UNIT);
/*	
	imu_discrete2real_dw(imu_velocity.dw.x, &imu_velocity.f.x, DELTA_VEL_UNIT);
	imu_discrete2real_dw(imu_velocity.dw.y, &imu_velocity.f.y, DELTA_VEL_UNIT);
	imu_discrete2real_dw(imu_velocity.dw.z, &imu_velocity.f.z, DELTA_VEL_UNIT);
*/
	/*
	imu_imu_velocity.x = (float)(_acc.x * DELTA_VEL_UNIT);
	imu_imu_velocity.y = (float)(_acc.y * DELTA_VEL_UNIT);
	imu_imu_velocity.z = (float)(_acc.z * DELTA_VEL_UNIT);
	*/
}
