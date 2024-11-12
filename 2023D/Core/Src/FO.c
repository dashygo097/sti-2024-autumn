#include "FO.h"
#include "signals.h"

double complex* DFT(int size ,double x[] )
{
    double complex X[size];
    double complex * A =X;
    if (size < 0 ){}
    else 
    {
        for (int m = 0; m < size ;m++)
        {
            X[m] = x[0] + 0*I;
            for (int n = 1 ; n < size ;n++)
            {
                X[m] += x[n] * (cos(2.0*M_PI*m*n/size) - I*sin(2.0*M_PI*m*n/size));
            } 
        }
    }
    return A;
}

int rev(int size , int index)
{
    int k = floor(log2(size)) , reg = 0;
    int ans = 0;
    for (int i =size/2 ; i>0 ; i/=2)
    {
        reg = index%2;
        ans += reg * pow(2 , k - 1) ;
        k--;
        index/= 2;
    }
    return ans;
}


double complex* rev_copy(int size , double a[])
{
    double complex A[size];
    double complex*X = A;
    for (int i = 0 ; i < size ; i++)
    {
        A[i] = a[rev(size,i)] + 0.0*I;
    }
    return X;
}

double complex* FFT(int size , double x[])
{
    double complex W[size/2];

    for (int i = 0 ; i < size/2 ; i++)
    {
        W[i] = cos(2*M_PI*i/size) + I*sin(2*M_PI*i/size);
    }

    double complex A[size];
    double complex *X = A;
    for (int i = 0;i < size ; i ++)
    {
    	A[i] = x[rev(size,i)] + 0*I;
    }
    
    int s ,m ,k ,j;
    double complex omega , t, u;

    for(s = 1 ; s <size ; s*=2)
    {
        m = s * 2;
        for ( k = 0 ; k< size ; k += m)
        {
            omega = 1;
            for (j = 0; j < m/2; j++)
            {
                t = omega * A[k+j+m/2];
                u = A[k+j];
                A[k+j] = u + t;
                A[k+j+m/2] = u - t;
                omega = omega * W[size/m];
            } 
        }
    }
    return X;

}

void FFT_Mag(int size, double x[])
{
    double cr , ci;
    double complex*X = FFT(size , x);
    for (int i = 0 ; i < size ; i++)
    {
        cr = (creal(X[i]) * creal(X[i]));

        ci = (cimag(X[i]) * cimag(X[i]));
        x[i] = (cr + ci) / size;
    }
}


void FFT_Mag_sqrt(int size , double x[])
{
    double complex* X = FFT(size , x);
    for (int i = 0 ; i < size ; i++)
    {
        x[i] = cabs(X[i]);
    }
}

void Square_Window(int size ,int left , int right ,double x[])
{
    for (int i = 0 ; i < size ; i ++)
    {
        if (i <= right && i >= left)
        {
            x[i] = 10*x[i];
        }
        else
        {
            x[i] = 0;
        }
    }
}


void Hamming(int size , int left , int right , double para , double x[])
{

    for (int i = 0 ; i < size ; i++)
    {
    	if (i < right && i >=  left)
    	{
    		x[i] = 10* x[i] * ((1 - para) - para* cos(2*M_PI*(i - left )/(right - left - 1)));
    	}
    	else
    	{
    		x[i] = 0;
    	}
    }
}




void Blackman(int size , int left , int right , double x[])
{

    for (int i = 0 ; i < size ; i++)
    {
    	if (i < right && i >=  left)
    	{
    		x[i] = 10* x[i] * ( 0.42 + 0.08* cos(4*M_PI*(i - left )/(right - left - 1)) - 0.5*cos(2*M_PI*(i - left )/(right - left - 1)));
    	}
    	else
    	{
    		x[i] = 0;
    	}
    }
}




