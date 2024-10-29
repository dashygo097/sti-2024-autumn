#ifndef SIGNAL_H
#define SIGNAL_H

#include <math.h>
#include <stdio.h>

// optional
#define FO_LENGTH 256

typedef struct wave_arg{
    double amp;
    double fre;
    double phase;
}wave_arg;

typedef struct AM_arg
{
    double fre;
    double U_c;
}AM_arg;


void SineWave_Generator(double wave[], int size, int n_periods, wave_arg arg);
void SineWave_AM_Generator(double wave[], int size, int n_periods, wave_arg arg, AM_arg am_arg);


#endif

