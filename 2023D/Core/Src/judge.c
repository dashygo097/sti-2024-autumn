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

int Analog_Judge(double x[], double v[])
{
    double bands[FO_LENGTH / 16];
    int bands_idx[FO_LENGTH / 16];
    double bands_sum = 0;
    int main_band_idx = 0;
    int n_bands = 0;
    int bands_gap = 0;
    char str[50];


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
    double threshold = main_band * 0.1;
    
    for(int i = main_band_idx - FO_LENGTH / 8; i < main_band_idx +  FO_LENGTH / 8 ; i++)
    {
        if(x[i] > threshold && x[i] > 50)
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
	HAL_UART_Transmit(&huart1,(uint8_t *)str , 30   ,HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);


	if (n_bands == 0)
	{
		return -1;
	}
	else if (n_bands == 1)
    {
        return 0;
    }
    else if (n_bands <= 3 )
    {
    	sprintf(str , "bands' gap: %d." , bands_gap);
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 15   ,HAL_MAX_DELAY);
    	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);

    	sprintf(str , "frequency: %.2lf kHz." , (double)bands_gap / 81.000);
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 20   ,HAL_MAX_DELAY);
    	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);

    	sprintf(str , "degree of moderation: %.2lf" ,(bands_sum - bands[n_bands / 2]) / bands[n_bands / 2]);
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 26   ,HAL_MAX_DELAY);
    	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);
        return 1; 
    } 
    else if (n_bands > 3 && n_bands < 20)
    {
    	sprintf(str , "bands' gap: %d." , bands_gap);
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 15   ,HAL_MAX_DELAY);
    	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);

    	sprintf(str , "frequency: %.2lf kHz." , (double)bands_gap / 81.000);
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 20   ,HAL_MAX_DELAY);
    	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);
    	// This params come from LR with maximum error about 1.0(often non-int modulation degree). So this should be optimized.
    	sprintf(str , "degree of modulation: %.3lf." ,(bands_sum / main_band - 1.119) / 1.479);
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 29   ,HAL_MAX_DELAY);
    	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);
        return 2; 
    }
    else
    {
        return Digital_Judge(x, v);
    }
}
    

int Digital_Judge(double x[], double v[])
{
    double main_band = 0;
    int main_band_idx = 0;
    char str[50];

    for (int i = 50; i < FO_LENGTH / 2 - 50; i++)
    {
        if (x[i] > main_band)
        {
            main_band = x[i];
            main_band_idx = i;
        }
    }

    double threshold = main_band * 0.2;
    int significant_bands = 0;
    double band_sum = 0;

    for (int i = main_band_idx - 100; i <= main_band_idx + 100; i++)
    {
        if (i >= 100 && i < FO_LENGTH / 2 - 100 && x[i] > threshold)
        {
            int flag = 1;
            for (int j = i - 2; j < i + 2; j++)
            {
                if (x[j] > x[i])
                    flag = 0;
            }
            if (flag == 1)
            {
                significant_bands++;
                band_sum += x[i];
            }
        }
    }

    for (int i = 50 ; i < FO_LENGTH / 2;  i++)
    {
    	if (abs(v[i] - v[i-1]) > 1)
    	{
    		return 5;
    	}
    }

	sprintf(str , "number of significant bands: %d." , significant_bands);
	HAL_UART_Transmit(&huart1,(uint8_t *)str , 31   ,HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1 ,(uint8_t *)"\n", 1 , HAL_MAX_DELAY);

    if (significant_bands < 2)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}


 


void Judger(int value)
{
	char str[200];

	if (value == -1)
	{
    	sprintf(str , "No signal.\n");
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 12   ,HAL_MAX_DELAY);
	}
	else if (value == 0)
    {
    	sprintf(str , "CW signal.\n");
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
    else if (value == 3)
    {
    	sprintf(str , "ASK signal.\n");
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 28   ,HAL_MAX_DELAY);
    }
    else if (value == 4)
    {
    	sprintf(str , "FSK signal.\n");
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 28   ,HAL_MAX_DELAY);
    }
    else if (value == 5)
    {
    	sprintf(str, "PSK signal.\n");
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 28   ,HAL_MAX_DELAY);
    }
    else
    {
    	sprintf(str , "Unknown signal.\n");
    	HAL_UART_Transmit(&huart1,(uint8_t *)str , 28   ,HAL_MAX_DELAY);
	}
}
