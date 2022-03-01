#pragma once

#include "code.h"
#include <stdbool.h>
#include <stdint.h>

extern uint64_t bytes_read;
extern uint64_t bytes_written;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
//BEHAVIOR
//---Reads all bites and returns how many bites have been read 

}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
//BEHAVIOR
//---Writes all the bites onto the dist form the bytes that were read
//---why? This is becauuse it takes a long time to access the disk, so we don't need to waste time acessing it multiple times


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
