#pragma once

#include "code.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

extern uint64_t bytes_read;
extern uint64_t bytes_written;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
//BEHAVIOR
//---Reads all bites and returns how many bites have been read 
	bytes_read = 0;
	int is_reading = 0;
	while (bytes_read == nbytes || is_writing == - 1) {	
		is_reading = read(infile, buf, nbytes);
		if (is_reading >= 1) {
			bytes_read += is_reading;
		} else {
			is_reading = -1;
		}
	}
	
	return bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
//BEHAVIOR
//---Writes all the bites onto the disk from the bytes that were read
//---why? This is becauuse it takes a long time to access the disk, so we don't need to waste time acessing it multiple times
	bytes_written = 0;
	int is_writing = 0;
	while (bytes_written == nbytes || is_writing == -1) {
		is_writing = write(outfile, buf, nbytes);
		if(is_writing >= 1) {
			bytes_written += is_writing;
		} else {
			is_writing = -1;
		}
	}

	return bytes_written;
}

bool read_bit(int infile, uint8_t *bit) {
//BEHAVIOR
//Return the Bit that the pointer in the array is pointing to
	
}

void write_code(int outfile, Code *c) {
//BEHAVIOR
//

}

void flush_codes(int outfile) {

}
