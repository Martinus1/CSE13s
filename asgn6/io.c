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
	while (bytes_read == nbytes || is_reading == -1) {	
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
//Read a block of bytes into a buffer and dole out bits one at a time
	uint8_t buffer[BLOCK];
	//gets the length of the file periodically
	int p = -1;
	if (bits_read == 0) {
		//This sets the bytes_read	
		read_bytes(infile, buffer, BLOCK);
		
		if(bytes_read < BLOCK) {
			p = (bytes_read * 8) + 1;
		}
		
		//SOURCE: Discord Prof. Long
		//This should return the one bit
		*bit = (buffer[bits_read / 8] >> (bits_read % 8) & 0x1);
		bits_read = (((bits_read) + 1) % (8 * BLOCK));
	} else {
		  //SOURCE: Discord Prof. Long
                  //This should return the one bit
                  *bit = (buffer[bits_read / 8] >> (bits_read % 8) & 0x1);
                  bits_read = (((bits_read) + 1) % (8 * BLOCK)); 	
		
	}
	
	if( p == bits_read) {
        	return false;
	} else {
	 	return true;
	}
}

void write_code(int outfile, Code *c) {
//BEHAVIOR
//!create static buffer 
//Each bit will be buffered into the buffer
//The bits will be buffered starting from the 0th bit in c(code)
	
	for (uint32_t i = 0; i < code_size(c); i++) {
		uint8_t bit = (c->bits[i / 8] >> (i % 8) & 0x1);
		//deletem if bit != 1
		if (bit == 1) {
			buffer[bits_added / 8] |= (0x1 << (bits_added % 8));
		} else {
			buffer[bits_added / 8] &= ~(0x1 << (bits_added % 8));
		}
	
		bits_added = (bits_added + 1) % (BLOCK * 8);
		
		if(bits_added == 0) {
			write_bytes(outfile, buffer, BLOCK);
			//clear_bites	
		}
		
	}
	
}

void flush_codes(int outfile) {
//BEHAVIOR
//Not guaranteed that buffed codes will alighn nicely with a block
// Possibility to have leftover bittes used by write_code() after the input has been completely encoded
// SO -> write out any leftover beffer bits + make sure last buts in the last byte are zeroed out
	uint8_t buffer[BLOCK];
	uint64_t leftover_bytes = bits_added % ((BLOCK * 8) / 8);
	uint64_t one_byte = (bits_added % 8);
	if (one_byte > 0) {
		leftover_bytes += 1;
	}
	write_bytes(outfile, buffer, bytes);
}


