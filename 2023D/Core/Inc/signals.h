#ifndef SIGNAL_H
#define SIGNAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// optional
#define FO_LENGTH 8192

typedef struct wave_arg{
    double amp;
    double fre;
    double phase;
}wave_arg;

typedef struct square_arg{
    double fre;
}square_arg;

typedef struct AM_arg{
    double fre;
    double U_c;
}AM_arg;

typedef struct FM_arg{
    double amp;
    double fre;
    double K_f;
}FM_arg;


void SineWave_Generator(double wave[], int size, double time, wave_arg arg);
void SineWave_AM_Generator(double wave[], int size, double time, wave_arg arg, AM_arg am_arg);
void SineWave_FM_Generator(double wave[], int size, double time, wave_arg arg, FM_arg fm_arg);

void ASK_Modulate(double wave[], int size, int nbits, wave_arg arg, wave_arg digital_arg);
void FSK_Modulate(double wave[], int size, int nbits, wave_arg arg, wave_arg digital_arg);

void ASK_Demodulate(double x[]);
void FSK_Demodulate(double x[]);
void PSK_Demodulate(double x[]);

void mod(double x, double mod);

#endif

