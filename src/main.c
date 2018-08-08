#include <stdio.h>
#ifdef __linux__ 
#include <unistd.h>
#elif _WIN32
#endif
#include <string.h>
#include "raw_wave.h"
#include "distortion.h"
#include "datatypes.h"
#include "merge_waves.h"

int main(int argc, char* argv[])
{
	/**
	commandline arguments: 
	1: input folder
	2: output file path
	3: minimal amount or random samples from input file
	4: maxium amount or random samples from input file
	5: minimal offset from input file
	6: maxium offset from input file

	OR 

	1: config file
	**/

	int result = 0;

	/**
	Raw_wave * wave;
	load_wave(&wave, "../../audio/1.wav");
	
	print_wave(wave, true);
	printf("----------------------\n");
	hamming_pointless_gain(wave);
	print_wave(wave, true);

	write_wave(wave, "../../audio/output.wav");
	destroy_wave(&wave);
	**/
	
	if (argc == 7) {
		printf("Merging waves..\n");
		Raw_wave * wave = merge_waves(argv[1], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
		printf("Saving wave file to %s..\n", argv[2]);
		hamming_pointless_gain(wave);
		write_wave(wave, argv[2]);
		destroy_wave(&wave);
		result = 0;
	} else if (argc == 2) {
		FILE *fp;
		char * c = malloc(1000);
		int i = 0;
		if (fp = fopen(argv[1], "r") != NULL) {
			do {
				*(c + i) = fgetc(fp);
			} while (*c != EOF);
		}
	} else {
		printf("No arguments given..\n");
		printf("Commandline arguments:\n");
		printf("1:\tinput folder\n2: \toutput file path\n3: \tminimal amount or random samples from input file\n4: \tmaxium amount or random samples from input file\n5: \tminimal offset from input file\n6: \tmaxium offset from input file");
		printf("\nOR\n\n");
		printf("1: path to config file\n");
		result = 1;
	}

	getchar();
	printf("Edn\n");
	return result;

}

