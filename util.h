#pragma once

#define MHz(x) ((x) * 1000 * 1000)
#define kHz(x) ((x) * 1000)

#define PI 3.141592653589

/**
	Main type for receiving I/Q samples from 8-bit ADCs (such as RTL-SDR's).
*/
typedef struct {
		uint8_t real, imag;
} cmplx_uint8_t;

typedef struct {
	float real, imag;
} cmplx_float_t;

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

inline void LIQR_sleep(int sleepMs)
{
#ifdef _WIN32
	Sleep(sleepMs);
#else
	usleep(sleepMs * 1000);
#endif
}