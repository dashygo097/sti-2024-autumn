
#ifndef INC_FO_H
#define INC_FO_H

#include <complex.h>

double complex* DFT(int size , double x[]);
double complex* FFT(int size , double x[]);
int rev(int size , int index);
void FFT_Mag(int size, double x[]);
void FFT_Mag_sqrt(int size , double x[]);
void Hamming(int size ,int left , int right ,double para , double x[]);
void Square_Window(int size ,int left , int right ,double x[]);
void Blackman(int size , int left , int right , double x[]);


#endif
