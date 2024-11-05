#include "judge.h"
#include "signals.h"

int Analog_Judge(double x[])
{
    double bands[FO_LENGTH / 2];
    double bands_idx[FO_LENGTH / 2];
    double bands_sum = 0;
    int n_bands = 0;
    int bands_gap = 0;


    // This can be optimized with specific threshold
    double main_band = 0;
    for (int i = 0; i < FO_LENGTH / 2; i++)
    {
        if (x[i] > main_band)
            main_band = x[i];
    }
    double threshold = main_band * 0.01; 
    
    for(int i = 10; i < FO_LENGTH / 2; i++) 
    {
        if(x[i] > threshold) 
        {
            bands_sum += x[i];
            bands[n_bands] = x[i];
            bands_idx[n_bands] = i;
            n_bands++;
        }
    }

    bands_gap = bands_idx[n_bands / 2 + 1] - bands_idx[n_bands / 2];
    printf("number of seperated bands: %d\n", n_bands);

    if (n_bands == 0)
    {
        return -1;
    }
    else if (n_bands == 1)
    {
        return 0;
    }
    else if (n_bands <= 3)
    {
        printf("degree of modulation: %.2lf\n", (bands_sum - bands[n_bands / 2]) / bands[n_bands / 2]);
        return 1; 
    } 
    else if (n_bands > 3 && n_bands < 20)
    {
        return 2; 
    }
    else
    {
        return Digital_Judge(x);
    }
}
    
int Digital_Judge(double x[])
{
    double main_band = 0;
    int main_band_idx = 0;
    
    for (int i = 50; i < FO_LENGTH / 2 - 50; i++)
    {
        if (x[i] > main_band)
        {
            main_band = x[i];
            main_band_idx = i;
        }
    }

    double threshold = main_band * 0.4;
    int significant_bands = 0;
    double band_sum = 0;
    
    for (int i = main_band_idx - 100; i <= main_band_idx + 100; i++)
    {
        if (i >= 100 && i < FO_LENGTH / 2 && x[i] > threshold)
        {
            int flag = 1;
            for (int j = i - 5; j < i + 5; j++)
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
    printf("number of significant bands: %d\n", significant_bands);

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
    if (value == -1)
        printf("No signal.\n");
    else if (value == 0)
        printf("Sin signal.\n");
    else if (value == 1)
        printf("AM signal.\n");
    else if (value == 2)
        printf("FM signal.\n");
    else if (value == 3)
        printf("ASK signal.\n");
    else if (value == 4)
        printf("FSK signal.\n");
    else 
        printf("No signal.\n");
}
