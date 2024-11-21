#ifndef JUDGE_H
#define JUDGE_H

#include <math.h>
#include <stdlib.h>

#include "signals.h"

int Analog_Judge(wave_arg arg, mod_arg mod_arg,  double x[], double v[]);
int Digital_Judge(double x[], double v[]);
void Judger(int value);


#endif
