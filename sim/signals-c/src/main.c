#include <stdio.h>
#include <stdlib.h>

#include "signals.h"
#include "judge.h"
#include "FO.h"

FILE* fp = NULL;
char tmp[50];

int main()
{

    double* v = (double*)malloc(sizeof(double) * FO_LENGTH);
    wave_arg arg = {1.0, 1000.0, 0.0};
    // AM_arg am_arg = {2000000.0, 1.0};
    // FM_arg fm_arg = {1.0, 2000000.0, 1000.0};
    wave_arg digital_arg = {1.0, 2000000.0, 0.0};
    
    // SineWave_AM_Generator(v, FO_LENGTH, 8, arg, am_arg);
    // SineWave_FM_Generator(v, FO_LENGTH, 16, arg, fm_arg);
    ASK_Modulate(v, FO_LENGTH, 32, arg, digital_arg);

    fp = fopen("../signals-py/waveform.txt", "w");
    for (int i = 0 ; i < FO_LENGTH; i++)
    {
        sprintf(tmp, "%.3lf\n", v[i]);
        fputs(tmp, fp);
    }
    fclose(fp);


    FFT_Mag_sqrt(FO_LENGTH, v);
    int value = Analog_Judge(v);
    Judger(value);

    fp = fopen("../signals-py/spectrum.txt", "w");
    for (int i = 0 ; i < FO_LENGTH; i++)
    {
        sprintf(tmp, "%.3lf\n", v[i]);
        fputs(tmp, fp);
    }
    fclose(fp);

    return 0;
}
