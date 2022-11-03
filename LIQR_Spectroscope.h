#pragma once
#include "LIQR_Layer.h"
#include "LIQR_Hopping_Receiver.h"
#include <cmath>
#include <fftw3.h>

class LIQR_Spectroscope : public LIQR_Layer
{
	fftwf_plan plan;

	fftwf_complex* fftwf_in;
	fftwf_complex* fftwf_out;

	cmplx_float_t* in;
	cmplx_float_t* out;

	float* levels;
	float* levels_filtered;
	float* levels_max_line;

public:
	float* get_levels_buffer();
	float* get_filtered_levels_buffer();
	float* get_max_line_levels_buffer();

	bool active;

	LIQR_Spectroscope(uint32_t len);

	void listen_to(LIQR_Layer* l);

	void update();

	void zero_maxline();

	void change_levels_buffer_length(int l);
};

