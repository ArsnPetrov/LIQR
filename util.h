#pragma once

#define MHz(x) ((x) * 1000 * 1000)
#define kHz(x) ((x) * 1000)

/**
	Main type for receiving I/Q samples from 8-bit ADCs (such as RTL-SDR's).
*/
typedef struct {
		uint8_t real, imag;
} cmplx_uint8_t;

typedef struct {
	float real, imag;
} cmplx_float_t;