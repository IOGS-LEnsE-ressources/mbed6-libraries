/**
 * FILENAME :        main_lib.cpp          
 *
 * DESCRIPTION :
 *       Robot 2 wheels / with Temp and Hum sensors.
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    13/mar/2023
 *
 *       LEnsE / Institut d'Optique Graduate School
 */

#include    "main_lib.h"

// For debugging
#define     DEBUG   1
UnbufferedSerial    my_pc(USBTX, USBRX);
char        charStr[128];


// Temperature Sensor
I2C         my_sensor_i2c(D14, D15);
DigitalOut  my_sensor_reset(D9);
TempHum_14_Click    my_sensor(&my_sensor_i2c, &my_sensor_reset);
// Value from the sensor
float       temperature, humidity;
// Collected data
float       temperatureI2C;
uint8_t     temperatureBytes[4];

// RF Transmission of data
nRF24L01P       nRF24_mod(D11, D12, D13, PA_12, PA_11, PB_12);
// MOSI, MISO, SCK, CSN, CE, IRQ
char        dataToSend[TRANSFER_SIZE] = {0};
char        dataReceived[TRANSFER_SIZE] = {0};



// Function to test conversion of data format
void    testConversion(void){
    // Test for Bytes to Float and Float to Bytes conversion
    temperature = 3.36;
    sprintf(charStr, "Temp = %f\r\n", temperature);
    my_pc.write(charStr, strlen(charStr));    

    my_sensor.floatToBytes(&temperature, temperatureBytes);

    for(int i = 0; i < 4; i++){
        sprintf(charStr, "%x ", temperatureBytes[i]);
        my_pc.write(charStr, strlen(charStr));    
    }
    
    temperatureI2C = my_sensor.bytesToFloat(temperatureBytes);
    sprintf(charStr, "\r\n NewTemp = %f\r\n", temperatureI2C);
    my_pc.write(charStr, strlen(charStr)); 
    // END - Test for Bytes to Float and Float to Bytes conversion
}


// Initialization function for the BT nRF24L01 module
void initNRF24(int frequency){
    nRF24_mod.powerUp();
    wait_us(100000);
    nRF24_mod.setAirDataRate(NRF24L01P_DATARATE_250_KBPS);
    nRF24_mod.setRfFrequency(frequency);
    wait_us(1000000);

    sprintf(charStr, "nRF24L01+ Frequency    : %d MHz\r\n",  nRF24_mod.getRfFrequency());
    my_pc.write(charStr, strlen(charStr)); 
    sprintf(charStr, "nRF24L01+ Data Rate    : %d kbps\r\n", nRF24_mod.getAirDataRate());
    my_pc.write(charStr, strlen(charStr)); 

    nRF24_mod.setTransferSize( TRANSFER_SIZE );
    nRF24_mod.setReceiveMode();
    nRF24_mod.enable();
}

// Receiving function for the BT nRF24L01 module
uint8_t receiveNRF24(char *data){
    uint8_t        rxDataCnt = 0;
    if ( nRF24_mod.readable() ) {
        // Read the data into the receive buffer
        rxDataCnt = nRF24_mod.read( NRF24L01P_PIPE_P0, data, TRANSFER_SIZE);
    }
    return rxDataCnt;
}

// Transmitting function for the BT nRF24L01 module
//  data : array of data to transmit
void        transmitNRF24(char *data){    
    nRF24_mod.write( NRF24L01P_PIPE_P0, data, TRANSFER_SIZE );
}