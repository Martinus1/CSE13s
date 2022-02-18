#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>
#include "randstate.h"

extern gmp_randstate_t state;

void randstate_init(uint64_t seed);

void randstate_clear(void);
