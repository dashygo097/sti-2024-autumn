#include <stdio.h>
#include <stdlib.h>

#include "signals.h"
#include "FO.h"

FILE* fp = NULL;
char tmp[50];

int main()
{


    double* v = (double*)malloc(sizeof(double) * FO_LENGTH);
    wave_arg arg = {1.0, 2000000.0, 0.0};
    AM_arg am_arg = {1000.0, 0.5};
    SineWave_AM_Generator(v, FO_LENGTH, 4, arg, am_arg);

    fp = fopen("../signals-py/waveform.txt", "w");
    for (int i = 0 ; i < FO_LENGTH; i++)
    {
        sprintf(tmp, "%.3lf\n", v[i]);
        fputs(tmp, fp);
    }
    fclose(fp);

    FFT_Mag(FO_LENGTH, v);

    fp = fopen("../signals-py/spectrum.txt", "w");
    for (int i = 0 ; i < FO_LENGTH; i++)
    {
        sprintf(tmp, "%.3lf\n", v[i]);
        fputs(tmp, fp);
    }
    fclose(fp);

    return 0;
}
