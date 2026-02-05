/**
 * FILENAME :        6DOF_IMU_FOXS8700.cpp          
 *
 * DESCRIPTION :
 *       6DOF_IMU_FOXS8700 / 3-axis accelerometer Sensor from NXP.
 *
 *       This module allows to measure XYZ acceleration
 *  with a specific I2C device - FXOS8700 from NXP
 *       More informations : https://www.nxp.com/docs/en/data-sheet/FXOS8700CQ.pdf
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    05/feb/2026
 *
 *       LEnsE / Institut d'Optique Graduate School
 */


#include <mbed.h>
#include "6DOF_IMU_FOXS8700.h"

Fxos8700::Fxos8700(I2C *_i2c){
    /* Initialisation of i2c module */
    if (_i2c){ delete __i2c; }
    __i2c=_i2c;
    __i2c->frequency(400000);   // Frequency of 400kHz
    thread_sleep_for(10);      // 10 ms
}

bool Fxos8700::isConnected(void){
  cmd[0] = FXOS8700CQ_WHOAMI;
  ack1 = __i2c->write(FXOS8700_ADD << 1, cmd, 1, true);
	ack2 = __i2c->read(FXOS8700_ADD << 1, data, 1);
  if(DEBUG_MODE) printf("Connect Acq = %d (W) / %d (R) \r\n", ack1, ack2);
  wait_us(1000);
	return (data[0] == FXOS8700CQ_WHOAMI_VAL);
}

void Fxos8700::init(void){
	// Accelerometer Control Register / 
  cmd[0] = FXOS8700CQ_CTRL_REG1;
	cmd[1] = 0x00;			// Standby Mode
  ack1 = __i2c->write(FXOS8700_ADD << 1, cmd, 2);
  if(DEBUG_MODE) printf("Standby Mode Acq = %d (W)\r\n", ack1);
  wait_us(1000);
	
	// Magnetometer /
  cmd[0] = FXOS8700CQ_M_CTRL_REG1;
	cmd[1] = 0x1F;			// auto calibration disabled - no one-shot magnetic reset - no one-shot magnetic measurement
	// 8x oversampling (for 200Hz) - select hybrid mode with accel and magnetometer active
  ack1 = __i2c->write(FXOS8700_ADD << 1, cmd, 2);
  if(DEBUG_MODE) printf("Magnetometer 1 Acq = %d (W)\r\n", ack1);
  wait_us(1000);	
	
	// Magnetometer /
  cmd[0] = FXOS8700CQ_M_CTRL_REG2;
	cmd[1] = 0x20;			// magnetometer registers to follow the accelerometer registers 
	//	retain default min/max latching even though not used
  ack1 = __i2c->write(FXOS8700_ADD << 1, cmd, 2);
  if(DEBUG_MODE) printf("Magnetometer 2 Acq = %d (W)\r\n", ack1);
  wait_us(1000);	
	
	// XYZ configuration /
  cmd[0] = FXOS8700CQ_XYZ_DATA_CFG;
	cmd[1] = 0x01;			// accelerometer range of +/-4g range with 0.488mg/LSB
  ack1 = __i2c->write(FXOS8700_ADD << 1, cmd, 2);
  if(DEBUG_MODE) printf("Data XYZ Config Acq = %d (W)\r\n", ack1);
  wait_us(1000);

	// Accelerometer Control Register / 
  cmd[0] = FXOS8700CQ_CTRL_REG1;
	cmd[1] = 0x0D;			// Activated in 200 Hz data rate - low noise - 16bits
  ack1 = __i2c->write(FXOS8700_ADD << 1, cmd, 2);
  if(DEBUG_MODE) printf("Activated Acq = %d (W)\r\n", ack1);
  wait_us(1000);

}

int Fxos8700::getStatus(void){
    cmd[0] = FXOS8700CQ_STATUS;
    ack1 = __i2c->write(FXOS8700_ADD << 1, cmd, 1, true);
    ack2 = __i2c->read(FXOS8700_ADD << 1, data, 1);
    if(DEBUG_MODE)  printf("Main Status Acq (W) = %d\r\n", ack1);
    if(DEBUG_MODE)  printf("Main Status Acq (R) = %d\r\n", ack2);
    return data[0];
}

bool Fxos8700::readDataValue(XYZ_DATA *accel, XYZ_DATA *magnet){
  cmd[0] = FXOS8700CQ_STATUS;
  ack1 = __i2c->write(FXOS8700_ADD << 1, cmd, 1, true);
  ack2 = __i2c->read(FXOS8700_ADD << 1, data, 13);
  if(DEBUG_MODE)  printf("Red Chan Acq (W) = %d\r\n", ack1);
  if(DEBUG_MODE)  printf("Red Chan Acq (R) = %d\r\n", ack2);
	if(data[0] > 0){
		accel->x_data = (int16_t)(((data[1] << 8) | data[2]))>> 2;
		accel->y_data = (int16_t)(((data[3] << 8) | data[4]))>> 2;
		accel->z_data = (int16_t)(((data[5] << 8) | data[6]))>> 2;
		magnet->x_data = (int16_t)(((data[7] << 8) | data[8]))>> 2;
		magnet->y_data = (int16_t)(((data[9] << 8) | data[10]))>> 2;
		magnet->z_data = (int16_t)(((data[11] << 8) | data[12]))>> 2;
		return true;
	}
	else{
		return false;
	}	
}
