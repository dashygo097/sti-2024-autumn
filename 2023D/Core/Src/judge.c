#include "judge.h"
#include "signals.h"
#include "FO.h"
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

int Analog_Judge(double x[])
{
    double bands[FO_LENGTH / 2];
    int bands_idx[FO_LENGTH / 2];
    double bands_sum = 0;
    int main_band_idx = 0;
    int n_bands = 0;
    int bands_gap = 0;
    char str[200];


    // This can be optimized with specific threshold
    double main_band = 0;
    for (int i = 100; i < FO_LENGTH / 2 - 100; i++)
    {
        if (x[i] > main_band)
        {
            main_band = x[i];
            main_band_idx = i;
        }
    }
    double threshold = main_band * 0.01;
    
    for(int i = main_band_idx - FO_LENGTH / 16; i < main_band_idx +  FO_LENGTH / 16 ; i++)
    {
        if(x[i] > threshold && x[i] > 20)
        {
        	int flag = 1 ;
        	for (int j = i - 2 ; j < i + 2 ; j++)
        	{
        		if (x[j] > x[i])flag = 0;
        	}
        	if (flag == 1)
        	{
        		bands_sum += x[i];
        		bands[n_bands] = x[i];
        		bands_idx[n_bands] = i;
        		n_bands++;
        	}
        }
    }

    bands_gap = bands_idx[n_bands / 2 + 1] - bands_idx[n_bands / 2];
	sprintf(str , "number of separated bands: %d." , n_bands);
	HAL_UART_Transmit(&huart1,(uint8_t *)str , 31   ,HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);
//    printf("number of separated bands: %d\n", n_bands);

    if (n_bands == 1)
    {
        return 0;
    }
    else if (n_bands <= 3)
    {
    	sprintf(str , "degree of moderation: %.2lf" ,(bands_sum - bands[n_bands / 2]) / bands[n_bands / 2]);
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 26   ,HAL_MAX_DELAY);
    	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);
        return 1; 
    } 
    else if (n_bands > 3 && n_bands < 20)
    {
        return 2; 
    }
    else
    {
        return -1;
    }
}
    
 
void Judger(int value)
{
	char str[200];

    if (value == 0)
    {
    	sprintf(str , "Sin signal.\n");
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 12   ,HAL_MAX_DELAY);
    }
    else if (value == 1)
    {
    	sprintf(str , "AM signal.\n");
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 11   ,HAL_MAX_DELAY);
    }
    else if (value == 2)
    {
    	sprintf(str , "FM signal.\n");
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 11   ,HAL_MAX_DELAY);
    }
    else 
    {
    	sprintf(str , "No analog moderated signal.\n");
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 28   ,HAL_MAX_DELAY);
    }
}
