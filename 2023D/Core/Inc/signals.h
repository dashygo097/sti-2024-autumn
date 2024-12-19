#ifndef SIGNAL_H
#define SIGNAL_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// optional
#define FO_LENGTH 8192

typedef struct wave_arg {
  double amp;
  double fre;
  double phase;
} wave_arg;

typedef struct mod_arg {
  double fre;
  double m;
} mod_arg;

void SineWave_Generator(double wave[], int size, double time, wave_arg arg);
void SineWave_AM_Generator(double wave[], int size, double time, wave_arg arg,
                           mod_arg am_arg);
void SineWave_FM_Generator(double wave[], int size, double time, wave_arg arg,
                           mod_arg fm_arg);

void SineWave_FM_Demodulate(double out[], double wave[], int size, double time,
                            mod_arg fm_arg, wave_arg arg);

void ASK_Modulate(double wave[], int size, int nbits, wave_arg arg,
                  wave_arg digital_arg);
void FSK_Modulate(double wave[], int size, int nbits, wave_arg arg,
                  wave_arg digital_arg);

void mod(double x, double mod);

#endif
