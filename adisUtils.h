#ifndef _ADISUTIL_H_
#define _ADISUTIL_H_

//#include <iostream>
//#include <sstream>
#include "types.h"
#include "bitOperation.h"
#include "communications.h"

//using namespace std;

/* PAGE ID 0 */
// Internal Temperature
#define TEMP_OUT         0x0E00
//Sequence Counter
#define	SEQ_CNT			0x0600
//Self-Test error flags
#define DIAG_STS		0x0A00

// GYRO Registers 
#define X_GYRO_LOW       0x1000
#define X_GYRO_OUT       0x1200
#define Y_GYRO_LOW       0x1400
#define Y_GYRO_OUT       0x1600
#define Z_GYRO_LOW       0x1800
#define Z_GYRO_OUT       0x1A00
// ACCELE Registers
#define X_ACCL_L         0x1C00
#define X_ACCL_H         0x1E00
#define Y_ACCL_L         0x2000
#define Y_ACCL_H         0x2200
#define Z_ACCL_L         0x2400
#define Z_ACCL_H         0x2600
// MAGNETOMETER Registers
#define X_MAGN_OUT		0x2800
#define Y_MAGN_OUT		0x2A00
#define Z_MAGN_OUT		0x2C00
// BAROMETER Registers
#define BAROM_LOW		0x2E00
#define BAROM_OUT		0x3000

// DELTA ANGLE Registers
#define X_DELTA_ANG_L    0x4000
#define X_DELTA_ANG_H    0x4200
#define Y_DELTA_ANG_L    0x4400
#define Y_DELTA_ANG_H    0x4600
#define Z_DELTA_ANG_L    0x4800
#define Z_DELTA_ANG_H    0x4A00
// DELTA VELOCITY Registers
#define X_DELTA_VEL_L    0x4C00
#define X_DELTA_VEL_H    0x4E00
#define Y_DELTA_VEL_L    0x5000
#define Y_DELTA_VEL_H    0x5200
#define Z_DELTA_VEL_L    0x5400
#define Z_DELTA_VEL_H    0x5600

/* PAGE ID 2 */
// GYRO OFFSET Registers
#define XGYRO_OFF_L      0x9000
#define XGYRO_OFF_H      0x9200
#define YGYRO_OFF_L      0x9400
#define YGYRO_OFF_H      0x9600
#define ZGYRO_OFF_L      0x9800
#define ZGYRO_OFF_H      0x9A00
// ACCL OFFSET Registers
#define XACCL_OFF_L      0x9C00
#define XACCL_OFF_H      0x9E00
#define YACCL_OFF_L      0xA000
#define YACCL_OFF_H      0xA200
#define ZACCL_OFF_L      0xA400
#define ZACCL_OFF_H      0xA600
// GYRO SCALE Registers
/*
#define XGYRO_SCL        0xC000
#define YGYRO_SCL        0xC200
#define ZGYRO_SCL        0xC400
// ACCL SCALE Registers
#define XACCL_SCL        0xC600
#define YACCL_SCL        0xC800
#define ZACCL_SCL        0xCA00
*/
#define XGYRO_SCL        0x8400
#define YGYRO_SCL        0x8600
#define ZGYRO_SCL        0x8800
// ACCL SCALE Registers
#define XACCL_SCL        0x8A00
#define YACCL_SCL        0x8C00
#define ZACCL_SCL        0x8E00
// HARD IRON MAGNETMETER Registers
#define HARD_IRON_X      0xA800
#define HARD_IRON_Y      0xAA00
#define HARD_IRON_Z      0xAC00
// SOFT IRON MAGNETMETER Registers
#define SOFT_IRON_S11    0xAE00
#define SOFT_IRON_S12    0xB000
#define SOFT_IRON_S13    0xB200
#define SOFT_IRON_S21    0xB400
#define SOFT_IRON_S22    0xB600
#define SOFT_IRON_S23    0xB800
#define SOFT_IRON_S31    0xBA00
#define SOFT_IRON_S32    0xBC00
#define SOFT_IRON_S33    0xBE00
// BAROMETER OFFSET Registers
#define BR_BIAS_LOW      0xC000
#define BR_BIAS_HIGH     0xC200

/* PAGE ID 3 */
#define GLOB_CMD         0x8200
#define GEN_CONFIG       0x8A00
#define DEC_RATE         0x8C00
#define NULL_CFG         0x8E00
// ALARM CONFIG
#define ALM_CONFIG1      0xA000
#define ALM_CONFIG2      0xA200
// GYRO ALARM 
#define XG_ALM_MAG       0xC000
#define YG_ALM_MAG       0xC200
#define ZG_ALM_MAG       0xC400
// ACCL ALARM
#define XA_ALM_MAG       0xC600
#define YA_ALM_MAG       0xC800
#define ZA_ALM_MAG       0xCA00
//FIRM Registers
#define FIRM_REV		0x7800
#define FIRM_DM			0x7A00
#define FIRM_Y			0x7C00

// BASE Registers
#define BASE_GYRO        X_GYRO_LOW
#define BASE_ACCL        X_ACCL_L
#define BASE_DELTA_ANG   X_DELTA_ANG_L
#define BASE_DELTA_VEL   X_DELTA_VEL_L

#define PAGE_ID    0x00

/*  Parameter Gain  */
#define TEMP_UNIT      0.00565
#define GYRO_UNIT      0.00000030517578125
#define ACCL_UNIT      0.00001220703125
#define DELTA_ANG_UNIT 0.000000127591192722320556640625
#define DELTA_VEL_UNIT 0.000000045471824705600738525390625
#define	MAGN_UNIT		0.1
//#define BARO_UNIT		0.00004
#define BARO_UNIT		0.0000000006103515625

#define TC_0_026SEC    0
#define TC_0_052SEC    1
#define TC_0_104SEC    2
#define TC_0_208SEC    3
#define TC_0_416SEC    4
#define TC_0_833SEC    5
#define TC_1_665SEC    6
#define TC_3_330SEC    7
#define TC_6_660SEC    8
#define TC_13_320SEC   9
#define TC_26_641SEC   10
#define TC_53_281SEC   11
#define TC_106_563SEC  12
#define TC_213_125SEC  13

#define BIAS_ENABLE_GYRO_X	0x0100
#define BIAS_ENABLE_GYRO_Y	0x0200
#define BIAS_ENABLE_GYRO_Z	0x0400
#define BIAS_ENABLE_ACCL_X	0x0800
#define BIAS_ENABLE_ACCL_Y	0x1000
#define BIAS_ENABLE_ACCL_Z	0x2000

typedef struct{
    WORD high;
    WORD low;
} dw_w;

typedef struct{
    DWORD x;
    DWORD y;
    DWORD z;
} axis_3_dw;

typedef struct{
    float x;
    float y;
    float z;
} axis_3_f;

typedef struct{
    axis_3_f f;
    axis_3_dw dw;
} axis;

extern axis  imu_gyro;
extern axis  imu_accele;
extern axis  imu_deltaAng;
extern axis  imu_deltaVel;
extern axis	imu_magneto;
extern WORD	imu_baro_w;
extern float	imu_baro_f;
extern WORD imu_temp_w;
extern float imu_temp_f;
extern axis  imu_angle;
extern axis  imu_velocity;
extern WORD  imu_firmrev;
extern WORD  imu_firmrev_dm;
extern WORD  imu_firmrev_y;
extern WORD  imu_diag;

//public:
void adisUtil_init(void);

void imu_clearAngle(void);
void imu_clearVelocity(void);

void imu_readSensor(void);
//string imu_allSensorSend(void);
void imu_allSensorSend_(char ret[15]);

void imu_setGyroScale_x(WORD arg);
void imu_setGyroScale_y(WORD arg);
void imu_setGyroScale_z(WORD arg);
WORD imu_getGyroScale_x(void);
WORD imu_getGyroScale_y(void);
WORD imu_getGyroScale_z(void);
void imu_setAcceleScale_x(WORD arg);
void imu_setAcceleScale_y(WORD arg);
void imu_setAcceleScale_z(WORD arg);
WORD imu_getAcceleScale_x(void);
WORD imu_getAcceleScale_y(void);
WORD imu_getAcceleScale_z(void);
void imu_scaleGyroIncrimental_x(int arg);
void imu_scaleGyroIncrimental_y(int arg);
void imu_scaleGyroIncrimental_z(int arg);
void imu_scaleAcceleIncrimental_x(int arg);
void imu_scaleAcceleIncrimental_y(int arg);
void imu_scaleAcceleIncrimental_z(int arg);
WORD imu_avg_dec_filter(float sps);
void imu_biasNull_setAverageTime(WORD tc, WORD bias);
void imu_biasNull(void);
void imu_softwareReset(void);
void imu_flashMemoryUpdate(void);
void imu_factoryCalibrationRestore(void);
void imu_selfTest(void);
void imu_getFirmwareRevision(void);

//private:
void imu_genericRead_3axis(axis_3_dw* read, unsigned int baseAddr);
void imu_genericIncremental_3axis(axis_3_dw* read, unsigned int baseAddr);
void imu_discrete2real_w(WORD w, float* f, double unit);
void imu_discrete2real_dw(DWORD dw, float* f, double unit);
void imu_discrete2real_3axis(axis_3_dw dw, axis_3_f* f, double unit);
void imu_dw2byteArray(DWORD arg, char ret[5]);
void imu_dw2byteArray_3axis(axis_3_dw dw, char ret[15]);
//string imu_dw2string_3axis(axis_3_dw dw);
void imu_writeRegister(WORD reg, WORD arg);
WORD imu_readRegister(WORD reg);

void imu_setPage(unsigned int page);

void imu_check_switch_pm(void);

// sensor data
void imu_getGyro(void);
void imu_getAccele(void);
void imu_getMagneto(void);
void imu_getDeltaAngle(void);
void imu_getDeltaVelocity(void);
void imu_getBarometer(void);
void imu_getTemperature(void);
// sensor data(incremental)
void imu_getAngle(void);
void imu_getVelocity(void);


#endif
