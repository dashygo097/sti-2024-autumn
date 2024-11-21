#include "signals.h"

void SineWave_Generator(double wave[], int size, double time, wave_arg arg)
{
    double time_step = (double)time / size;
    for (int i = 0; i < size; i++)
    {
        wave[i] = arg.amp * sin(2 * M_PI * i * time_step + arg.phase);
    }
}

void SineWave_AM_Generator(double wave[], int size, double time, wave_arg arg, mod_arg am_arg)
{
    double time_step = time / size;
    for (int i = 0 ; i < size; i++)
    {
        wave[i] =(am_arg.m + arg.amp * sin(2 * M_PI * i * time_step + arg.phase)) *
            sin(2 * M_PI * i * time_step * am_arg.fre / arg.fre + arg.phase);
    }
}

void SineWave_FM_Generator(double wave[], int size, double time, wave_arg arg, mod_arg fm_arg)
{
    double time_step = time / size;
    for (int i = 0 ; i < size; i++)
    {
        wave[i] = sin(2 * M_PI * i * time_step * fm_arg.fre / arg.fre+
            arg.amp * fm_arg.m / arg.fre * sin(2 * M_PI * i * time_step ));
    }
}


void SineWave_FM_Demodulate(double out[], double wave[], int size, double time, mod_arg fm_arg, wave_arg arg)
{
    double w1[FO_LENGTH] = {0};
    double w2[FO_LENGTH] = {0};
    wave_arg arg_delta = {arg.amp, arg.fre, arg.phase + M_PI / 2};

    SineWave_Generator(w1, FO_LENGTH, time * fm_arg.fre / arg.fre, arg);
    SineWave_Generator(w2, FO_LENGTH, time * fm_arg.fre / arg.fre, arg_delta);

    for (int i = 1; i < FO_LENGTH; i++)
    {
        w1[i] = w1[i] * wave[i];
        w1[i] = 0.008 * w1[i] + 0.992 * w1[i - 1];
        w2[i] = w2[i] * wave[i];
        w2[i] = 0.008 * w2[i] + 0.992 * w2[i - 1];
    }
    out[0] = 0;
    for (int i = 1; i < FO_LENGTH; i++)
    {
        out[i] = w1[i - 1] * w2[i] - w1[i] * w2[i - 1];
        out[i] = out[i] / (w1[i] * w1[i] + w2[i] * w2[i]);
        out[i] = 0.0005 * out[i] + 0.9995 * out[i - 1];
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
