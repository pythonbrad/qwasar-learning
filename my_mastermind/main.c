#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>


void gen_secret(char* secret) {
	char start = '0' + (rand() % 10);
	// to avoid 2 1 0 x
	// 7 8 9 x
	char sign = start < '3';

	while (*secret != '\0') {
		*secret = start;
	       
		start = start + 1 * (sign ? 1 : -1);
		secret++;
	}
}

void start_game(char* secret, int max_attempt) {
	int round = 0;
	char entry;

	int misplacement = 0;
	int wellplacement = 0;
	int index = 0;

	// printf("Game started with secret=%s max_attempt=%d\n\n", secret, max_attempt);
	printf("Will you find the secret code?\n");
	printf("Please enter a valid guess\n");

	while (round < max_attempt) {
		index = 0;
		misplacement = 0;
		wellplacement = 0;

		printf("---\n");
        	printf("Round %d\n>", round);
		fflush(stdout);

		// Read until the reach the secret length, new line or EOF
		while (read(0, &entry, 1) > 0) {
			if (entry == EOF || entry == '\n') {
				break;
			}
            
            		// Make sure the input is flushed when you don't need it anymore
            		if (secret[index] == '\0') continue;

			if (strchr(secret, entry) == NULL) {
				// pass
			} else if (secret[index] == entry) {
				wellplacement++;
			} else {
				misplacement++;
			}

			index++; 
		}

		// Whether wellplacement match at the end
		if (wellplacement == index && secret[index] == '\0') {
			printf("Congratz! You did it!\n");
			break;
		} else {
			printf("Well placed pieces: %d\n", wellplacement);
			printf("Misplaced pieces: %d\n", misplacement);
		}
		
		round++;
	}
}


int main(int argc, char** argv) {
	// char pieces[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int arg_idx;
	// 4 characters + '\0'
	char secret[5] = "0000\0";
	int max_attempt = 10;

	// cli
	char* option;
	char* value;

	// generate the seed
	srand(time(NULL));
	
	if (argc < 2) {
		printf("Usage: program [-c \"01234\"] [-t 10]\n");
		printf("\t-c Set the secret code (4 distinc numbers between 0-9)\n");
		printf("\t-t Set the maximun number of attempt\n");
	}
	
	for (arg_idx = 2; arg_idx < argc; arg_idx = arg_idx + 2) {
		option = argv[arg_idx-1];
		value = argv[arg_idx];

		if (strcmp(option, "-c") == 0 && strlen(value) == 4) {
			strncpy(secret, value, 4);
		} else if (strcmp(option, "-t") == 0) {
			max_attempt = atoi(value);
		} else {
			printf("option '%s' invalid", option);

			return 1;
		}
	}

	if (strcmp(secret, "0000") == 0) gen_secret(secret);

	start_game(secret, max_attempt);

	return 0;
}
