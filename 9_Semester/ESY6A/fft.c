#include "system/task_fft.h"
#include "system/data_channel.h"
#include "system/Complex.h"
#include "system/float_word.h"
#include <stdio.h>
#include <complex.h>
#include <math.h>

#define N 1024
#define T 5

void calcFFT1024(float *x);

int task_fft_run( void * task ) {

    // TODO
	fft_config * fft = (fft_config * ) task;
	float_word fftInput;	
	float fftArray[N];						
	
	// read data from FIFO
	for( uint32_t i = 0; i < DATA_CHANNEL_DEPTH; i++ )
	{
		data_channel_read(fft->base.sources[0], &fftInput.word);
		fftArray[i] = fftInput.value;
		//printf("%f, ", fftArray[i]);
	}
	
	// calculate FFT
	calcFFT1024(fftArray);

	// write data to FIFO
	for( uint32_t i = 0; i < DATA_CHANNEL_DEPTH; i++ )
	{
		fftInput.value = fftArray[i];
		data_channel_write(fft->base.sink, fftInput.word);
		//printf("%f, ", fftArray[i]);
	}

    return 0;
}

void calcFFT1024(float *x)
{
    complex float fft[N]; // Complex array for FFT-Calculation

    // Write input to complex array
    for (int i = 0; i < N; i++)
    {
        fft[i] = x[i];
    }

    // Algorithmus 2.2.2
    for (int k = 0; k < N; k++)
    {
        // Algorithmus 2.2.1
        int m = k;
        int j = 0;
        for (int q = T ; q > 0; q--)
        {
            int s = m / 4;
            j = 4 * j + m - s * 4;
            m = s;
        }
        if (j > k)
        {
            complex float hilf = fft[j];
            fft[j] = fft[k];
            fft[k] = hilf;
        }
    }

    // Algorithmus 2.4.1
    for (int i = 1; i <= T; i++)
    {
        int L = pow(4, i);
        int r = N / L;
        int L2 = L / 4;

        for (int j = 0; j < L2; j++)
        {
            complex float w = cos((2 * M_PI * j) / L) - I * sin((2 * M_PI * j) / L);
            complex float w2 = w * w;
            complex float w3 = w * w2;

            for (int k = 0; k < r; k++)
            {
                complex float alpha = fft[k * L + j];
                complex float beta = w * fft[k * L + L2 + j];
                complex float gama = w2 * fft[k * L + 2 * L2 + j];
                complex float delta = w3 * fft[k * L + 3 * L2 + j];

                complex float r0 = alpha + gama;
                complex float r1 = alpha - gama;
                complex float r2 = beta + delta;
                complex float r3 = beta - delta;

                fft[k * L + j] = r0 + r2;
                fft[k * L + L2 + j] = r1 - I * r3;
                fft[k * L + 2 * L2 + j] = r0 - r2;
                fft[k * L + 3 * L2 + j] = r1 + I * r3;
            }
        }
    }

	// Achsenskalierung
    for (int i = 0; i < N; i++)
    {
		// Betrag von FFT-Komplex in Ausgang schreiben
        x[i] = sqrt(creal(fft[i] * creal(fft[i]) + cimag(fft[i]) * cimag(fft[i])));
		// Skalierung mit N/2
        x[i] = x[i] / (N / 2);
    }
	// Sonderbehandlung x=0 -> nochmal halbieren da doppelt
	x[0] = x[0] / 2;
		
	printf("Done\n");
}

