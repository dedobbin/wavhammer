#include <math.h>
#include <stdio.h>
#include "distortion.h"

/* amount will be added to every > 0 sample, and extracted from samples < 0, if value under- or overflows, it's set to min or max value*/
void distortion(Raw_wave * wave, long amount)
{
	if (bits_per_sample(wave) == 16) {
		//-32768 to 32767
		const MAX = 32767;
		const MIN = -32768;

		int i;
		for (i = 0; i < num_samples(wave); i++) {
			int16_t sample = get_sample(wave, i);
			if (sample > 0) {
				if (sample + amount < sample)
					set_sample(wave, i, MAX);
				else
					set_sample(wave, i, sample + amount);
			}
			else if (sample < 0) {
				if (sample - amount > sample)
					set_sample(wave, i, MIN);
				else
					set_sample(wave, i, sample - amount);
			}
		}
	}
	else {
		printf("distortion: Not implemented for %d bits per sample\n", bits_per_sample(wave));
	}
}

void hamming_kapot(Raw_wave * dst)
{
	int i = 0;
	for (i = 0; i < datasize(dst); i++) {
		dst->data_chunk->audiodata[i] |= dst->data_chunk->audiodata[random(0, i)];
	}
}

void hamming_distortion(Raw_wave * wave, long amount)
{
  int blockAlign = block_align(wave);
  int numSamples = num_samples(wave);
  unsigned long max = pow(2, (blockAlign * 8))-1;
  
  int i;
  for (i = 0; i < numSamples; ++i){
    long sample = get_sample(wave,i);
    set_sample(wave, i, sample + amount);
    long newSample = get_sample(wave, i);
    if (newSample< sample)
      set_sample(wave, i , max);
  }
}

void hamming_pointless_distortion(Raw_wave * wave)
{
  int i = 0;
  for (i=0; i < datasize(wave); i++){
    wave->data_chunk->audiodata[i]*=2;
  }
}

void hamming_distortion2(Raw_wave * dst)
{

	int i = 0;
	for (i = 0; i < datasize(dst); i++) {
		dst->data_chunk->audiodata[i] *= 2;
	}
}

void hamming_distortion3(Raw_wave * dst)
{

	int i = 0;
	for (i = 0; i < datasize(dst) - 1; i++) {
		dst->data_chunk->audiodata[i] |= dst->data_chunk->audiodata[i + 1];
	}
}
