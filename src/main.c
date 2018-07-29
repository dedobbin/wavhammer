#include <stdio.h>
#ifdef __linux__ 
#include <unistd.h>
#elif _WIN32
#endif
#include <string.h>
#include "raw_wave.h"
#include "hamming.h"
#include "linked_list.h"
#include "datatypes.h"


int main(int argc, char* argv[])
{
  printf("loading .wavs..\n");
  Raw_wave * waveOne;
  if (!load_wave(&waveOne, "../../audio/fdgfdg.wav")) {
      printf("Could not init wave one");
  }

  Raw_wave * waveTwo;
  if (!load_wave(&waveTwo, "../../audio/tone.wav")) {
      printf("Could not init wave two");
  }

  printf("===================\n");
  print_wave(waveTwo);
  printf("===================\n");

  printf("merging .wavs..\n");
  insert_samples(waveOne, waveTwo, num_samples(waveTwo) * 2, num_samples(waveOne)/4);

  printf("===================\n");
  print_wave(waveOne);
  printf("===================\n");

  printf("Writing .wav to disk..\n");
  write_wave(waveOne, "../../audio/output.wav");

  printf("Done\n");
  getchar();
  return 0;

}

