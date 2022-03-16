#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <getopt.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>

int main(int argc, char **argv) {

    char data = "lib.db"
    char noise = "noise.txt"
    int matches = 5;
    int noise_count = 100;
    bool isHelp = false;
    char opt;

    

    while ((opt = getopt(argc, argv, "i:o:vh")) != -1) {
	switch (opt) {

	case 'd':
		//Specifies the database of authors and texts (def: lib.db)
		data = optarg;
		break;
	case 'n':
		//Specify path to file of noise words to filter out. The default is noise.txt
		 noise = optarg
		break; 
	case 'k':
		//Specify the number of matches. The default is 5
		matches = atoi(optarg);
		break;
	case 'l':
		//specify the number of noise words to filter out. The default is 100
		noise_count = atoi(optarg);
		break;
	case 'e':
		//Set the distance metric to use as the Euclidean distance. This should be the default metric if no other distance metric is specified.
		break;
	case: 'm':
		//Set the distance metric to use as the Manhattan distance
		break;
	case 'c':
		//Set the distance metric to use as the cosine distance
		break;
	case 'h':
		// Program help and usage
		isHelp = true;
		break;
	default:
		printf("Nothing selected");
		return 1;
	}

    }
	
        if (isHelp == true) {
        printf("SYNOPSIS\n");
        printf("Plagiarism Detector\n\n");

        printf("USAGE\n");
        printf("./encrypt [OPTIONS]\n\n");

        printf("OPTIONS\n");
        printf("-h Print Program Synopsis/Usage\n");
        printf("-i infile specifies the input file (default: stdin)\n");
        printf("-o specifies the output file (default: stdout)\n");
        printf("-n pvfile Public Key File(default: rsa.pub)\n ");
    }

    //Create Text 
    Text text = text_create();
	
    // Create new anonymous text from text passed in to stdin. This is the text that you want to identify. Remember to filter out all the noise words in the noise word Text that you just created.
    Text text = text_create();
   
    //Open up the database of authors and text files
       


    return 0;


}

