/* FFT on G431KB */
/* git clone https://github.com/STMicroelectronics/STM32CubeG4.git   in C:/ */

#include "mbed.h"
#include "arm_math.h"
#include "arm_common_tables.h"
#include "arm_const_structs.h"

#define SAMPLES                 512
/* 256 real party and 256 imaginary parts */
#define FFT_SIZE                SAMPLES / 2
/* FFT size is always the same size as we have samples, so 256 in our case */
#define OUTPUT_GAIN             100.0
/* Gain on the output values - for better display */

float32_t Input[SAMPLES];
float32_t Output[FFT_SIZE];

bool      trig=0;         // sampling blocking semaphore
int       indice = 0;

DigitalOut myled(PB_0);
AnalogIn   myADC(PA_0);
AnalogOut  myDAC(PA_4);
Ticker     timer;

void sample(){
        myled = 1;
        if(indice < SAMPLES){
                Input[indice] = myADC.read() - 0.5f;
                // Real part NB removing DC offset
                Input[indice + 1] = 0;
                // Imaginary Part set to zero
                indice += 2;
        }
        else{ trig = 0; }
        myled = 0;
}

int main() {
        float maxValue;            // Max FFT value is stored here
        uint32_t maxIndex;         // Index in Output array where max value is

        while(1) {
                if(trig == 0){
                        timer.detach();
                        // arm_cfft_sR_f32_lenXXX, where XXX is the samples number, here 256
                        arm_cfft_f32(&arm_cfft_sR_f32_len256, Input, 0, 1);

                        // FFT calculation and storage of the magnitude of the complex FFT values in the Output array
                        arm_cmplx_mag_f32(Input, Output, FFT_SIZE);
                        Output[0] = 0;

                        // Analog display of the FFT
                        myDAC=1.0f;     // Sync pulse
                        wait_us(10);
                        myDAC=0.0f;
                        // Display all the values
                        for(int i=0; i < FFT_SIZE/2; i++){
                                myDAC.write(Output[i]);
                        }
                        myDAC=0.0f;

                        // Restart sampling
                        trig = 1;
                        indice = 0;
                        timer.attach(&sample,40us);    //40us 25KHz sampling rate
                }
        }
}