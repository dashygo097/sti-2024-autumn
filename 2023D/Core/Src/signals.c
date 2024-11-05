#include "signals.h"

void SineWave_Generator(double wave[], int size, double time, wave_arg arg)
{
    double time_step = (double)time / size;
    for (int i = 0; i < size; i++)
    {
        wave[i] = arg.amp * sin(2 * M_PI * i * time_step + arg.phase);
    }
}

void SineWave_AM_Generator(double wave[], int size, double time, wave_arg arg, AM_arg am_arg)
{
    double time_step = time / size;
    for (int i = 0 ; i < size; i++)
    {
        wave[i] =(am_arg.U_c + arg.amp * sin(2 * M_PI * i * time_step + arg.phase)) * 
            sin(2 * M_PI * i * time_step * am_arg.fre / arg.fre + arg.phase);
    }
}

void SineWave_FM_Generator(double wave[], int size, double time, wave_arg arg, FM_arg fm_arg)
{
    double time_step = time / size;
    for (int i = 0 ; i < size; i++)
    {
        wave[i] = fm_arg.amp * sin(2 * M_PI * i * time_step * fm_arg.fre / arg.fre+
            arg.amp * fm_arg.K_f / arg.fre * sin(2 * M_PI * i * time_step ));
    }
}



void ASK_Modulate(double wave[], int size, int nbits, wave_arg arg, wave_arg digital_arg)
{
    double time_step = (double)nbits / size;
    int digital_step = size / nbits;
    int bit = 0;
    for (int i = 0 ; i < size; i++)
    {
        if ((i % digital_step) == 0)
        {
            bit = rand() % 2;
            printf("bit%d: %d\n", i / digital_step, bit);
        } 
        wave[i] = arg.amp * sin(2 * M_PI * i * time_step * digital_arg.fre / arg.fre + arg.phase) * bit;
    }

}




void FSK_Modulate(double wave[], int size, int nbits, wave_arg arg, wave_arg digital_arg)
{

    double time_step = (double)nbits / size;
    int digital_step = size / nbits;
    int bit = 0;
    double freq;
    double phase = arg.phase;
    for (int i = 0; i < size; i++)
    {
        if ((i % digital_step) == 0)
        {
            bit = rand() % 2;
            printf("bit%d: %d\n", i / digital_step, bit);
        }

        freq = bit ? digital_arg.fre - arg.fre: digital_arg.fre;
        wave[i] = arg.amp * sin(phase);
        phase += 2 * M_PI * time_step * freq / arg.fre;
        mod(phase, 2 * M_PI);
    }

}

void mod(double x, double mod)
{
    x = x - (int)(x / mod) * mod;
}
