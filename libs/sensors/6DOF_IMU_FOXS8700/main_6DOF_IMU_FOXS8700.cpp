/**
 * FILENAME :        main_6DOF_IMU_FOXS8700.cpp          
 *
 * DESCRIPTION :
 *       6DOF_IMU_FOXS8700 / 3-axis accelerometer Sensor from NXP.
 *			Testing program.
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    05/feb/2026
 *
 *       LEnsE / Institut d'Optique Graduate School
 */
 

#include "mbed.h"
#include "6DOF_IMU_FOXS8700.h"

#define WAIT_TIME_MS 5 
DigitalOut led1(LED1);

/// Create an I2C interface with specific pins : SDA / SCL
I2C               my_i2c(D14, D15); // SDA / SCL
/// Create a 6DOF module connection with an I2C interface
Fxos8700      		my_sensor(&my_i2c);

/// Create 2 data structures to collect accelerometer/magnetometer values
XYZ_DATA	accelero;
XYZ_DATA	magneto;

int main()
{
	printf("Test.\n");
	/// PowerUp the module
	printf("Connected ? %d\r\n", my_sensor.isConnected());
	// Get Status
	printf("Status ? %d\r\n", my_sensor.getStatus());
	/// Init the module
	my_sensor.init();
	
	// Get Status
	printf("Status ? %d\r\n", my_sensor.getStatus());
	
	

	while (true)
	{
			if(my_sensor.readDataValue(&accelero, &magneto)){
				printf("New Data / X_Accel = %d \r\n", accelero.x_data);
			}
			else{
				printf("NO DATA \r\n");
			}
			thread_sleep_for(WAIT_TIME_MS);
	}
}