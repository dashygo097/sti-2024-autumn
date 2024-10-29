#include "signals.h"

void SineWave_Generator(double wave[], int size, int n_periods, wave_arg arg)
{
    double time_step = (double)n_periods / size;
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
        wave[i] =(am_arg.U_c + arg.amp * sin(2 * M_PI * i * time_step * arg.fre / am_arg.fre + arg.phase)) * 
            sin(2 * M_PI * i * time_step + arg.phase);
    }
}

void SineWave_FM_Generator(double wave[], int size, double time, wave_arg arg, FM_arg fm_arg)
{
    double time_step = time / size;
    for (int i = 0 ; i < size; i++)
    {
        wave[i] = arg.amp * sin(arg.phase + 2 * M_PI * i * time_step +
            fm_arg.amp * fm_arg.K_f / fm_arg.fre * sin(2 * M_PI * i * time_step * fm_arg.fre / arg.fre));
    }
}
