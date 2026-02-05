/**
 * FILENAME :        6DOF_IMU_FOXS8700.h        
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
 
#ifndef __DOF_IMU_HEADER_H__
#define __DOF_IMU_HEADER_H__

#include <mbed.h>
 
/** Constant definition */
#define     DEBUG_MODE            1

#define   FXOS8700_ADD				0x1E
#define 	FXOS8700CQ_WHOAMI 		0x0D 
#define 	FXOS8700CQ_WHOAMI_VAL 	0xC7

#define 	FXOS8700CQ_STATUS 		0x00 
#define 	FXOS8700CQ_XYZ_DATA_CFG 0x0E 
#define 	FXOS8700CQ_CTRL_REG1 	0x2A 
#define 	FXOS8700CQ_M_CTRL_REG1 	0x5B
#define 	FXOS8700CQ_M_CTRL_REG2 	0x5C

typedef struct{
	int16_t 	x_data;
	int16_t 	y_data;
	int16_t 	z_data;
}XYZ_DATA;


/**
 * @class Fxos8700
 * @brief Access to the Fxos8700 module from NXP (included on 6DOF IMU 3 from MikroE)
 * @details     Fxos8700 module allows to measure 3 axis acceleration.
 */
class Fxos8700{
     private:
        /// Command to send
        char    cmd[2];
        /// Received Data
        char    data[15];
        /// Acknowledgement variables
        char    ack1, ack2;
        
        /// I2C interface pins 
        I2C     *__i2c = NULL;

    public:
        /**
        * @brief Simple constructor of the FXOS8700 module class.
        * @details Create a FXOS8700 object with
        *    an I2C interface
        *    I2C communication will be initialized at 400kHz
        * @param _i2c SPI interface not initialized
        */
        Fxos8700(I2C *_i2c);

        /**
        * @brief Detection of the sensor / WHOAMI register
        * @details Send a request to get the WHOAMI register and check its value
        */
        bool isConnected(void);

        /**
        * @brief Initiatlization in "normal" mode / 4g range
        * @details Initialize the sensor with...
				* 	...
				*  	Values from section 13.4 of the FXOS8700 NXP datasheet.
        */
        void init(void);

        /**
        * @brief Return the status of the module
        * @return the part status of the module - default 0x00 if not data ready, 0xFF is all data ready
        */
        int getStatus(void);

        /**
        * @brief Read Status register and XYZ acceleration/magneto values
        * @details Read the STATUS register (to control if new data are present) then
        *		read the XYZ (2 bytes / axis) values for accelerometer, then magnetometer
        * @return True if new data. 
        */
        bool readDataValue(XYZ_DATA *accel, XYZ_DATA *magnet);
};

#endif