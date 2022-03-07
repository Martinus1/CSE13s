#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include "code.h"
#include "io.h"

uint64_t bytes_read;
uint64_t bytes_written;
uint64_t bits_read, bits_added;

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    //BEHAVIOR
    //---Reads all bites and returns how many bites have been read
    int number_of_bytes_read = 0;
    bool eof = false;

    while (!eof && number_of_bytes_read <= nbytes) {
        int num_read_call = read(infile, buf, nbytes);

        if (num_read_call == -1) {
            return -1;
        }

        if (num_read_call == 0) {
            // EOF
            eof = true;
        }

        number_of_bytes_read += num_read_call;
    }

    bytes_read += number_of_bytes_read;
    return number_of_bytes_read;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    //BEHAVIOR
    //---Writes all the bites onto the disk from the bytes that were read
    //---why? This is becauuse it takes a long time to access the disk, so we don't need to waste time acessing it multiple times
    int number_of_bytes_written = 0;

    while (number_of_bytes_written < (uint64_t) nbytes) {
        int num_write_call = write(outfile, buf, nbytes);

        if (num_write_call == -1) {
            return -1;
        }

        number_of_bytes_written += num_write_call;
    }

    bytes_written += number_of_bytes_written;
    return number_of_bytes_written;
}

bool read_bit(int infile, uint8_t *bit) {
    //BEHAVIOR
    //Read a block of bytes into a buffer and dole out bits one at a time
    uint8_t buffer[BLOCK];
    //gets the length of the file periodically
    uint64_t file_length = UINT_LEAST64_MAX;

    if (bits_read < file_length) {
        //This sets the bytes_read
        read_bytes(infile, buffer, BLOCK);

        //This should return the one bit
        *bit = (buffer[bits_read / 8] >> (bits_read % 8) & 0x1);
        bits_read = (((bits_read) + 1) % (8 * BLOCK));

        if (bytes_read < BLOCK) {
            file_length = (bytes_read * 8) + 1;
            return false;
        }
    }

    return true;
}

void write_code(int outfile, Code *c) {
    //BEHAVIOR
    //!create static buffer
    //Each bit will be buffered into the buffer
    //The bits will be buffered starting from the 0th bit in c(code)
    uint8_t buffer[BLOCK];

    for (uint32_t i = 0; i < code_size(c); i++) {
        uint8_t bit = (c->bits[i / 8] >> (i % 8) & 0x1);
        //deletem if bit != 1
        if (bit == 1) {
            buffer[bits_added / 8] |= (0x1 << (bits_added % 8));
        } else {
            buffer[bits_added / 8] &= ~(0x1 << (bits_added % 8));
        }

        bits_added = (bits_added + 1) % (BLOCK * 8);

        if (bits_added == 0) {
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
    write_bytes(outfile, buffer, BLOCK);
}
