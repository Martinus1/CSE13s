#pragma once

#include <stdint.h>
#include <gmp.h>

extern gmp_randstate_t state;

void randstate_init(uint64_t seed) {
	gmp_randin_mp(state);
	gmp_randseed_ui(state, seed);

	return;
}

void randstate_clear(void) {
	gmp_randclear(state);
	return;
}
