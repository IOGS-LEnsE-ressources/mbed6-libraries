/**
  Example based on LCD_Paint LCD Paint application
  (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Display/LCD_Paint/readme.txt 
  * @author  MCD Application Team
  * @brief   
*/

PINOUT :

D5 / PA_2		Random Analog Input (not connected) 
					- ADC1_IN / 28 cycles / Channel 2
D6 / PA_6		SYNC0 - Interrupt In / Start Color 0
D9 / PA_7		SYNC - Interrupt In / Clk sync
D12/ PB_14		MODE - Mode Bingo or Smooth (from L432)


TO DO : 
 - Random with Analog in (for number selection - https://controllerstech.com/stm32-adc1-single-channel-polling-mode/)
 - Synchronize with clk input (Interrupt - https://deepbluembedded.com/stm32-external-interrupt-example-lab/ )
 - Synchronize color start and mode