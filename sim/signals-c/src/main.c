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
    AM_arg am_arg = {1000.0, 0.8};
    FM_arg fm_arg = {1.0, 500000.0, 500000.0};
    // SineWave_AM_Generator(v, FO_LENGTH, 4, arg, am_arg);
    SineWave_FM_Generator(v, FO_LENGTH, 32, arg, fm_arg);

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
