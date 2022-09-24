#include "LIQR_Spectroscope.h"
#include "LIQR_Receiver.h"

LIQR_Spectroscope::LIQR_Spectroscope(uint32_t len)
{
	length = len;
	type = LAYER_SPECTROSCOPE;

	fftwf_in = fftwf_alloc_complex(length);
	fftwf_out = fftwf_alloc_complex(length);
	plan = fftwf_plan_dft_1d(length, fftwf_in, fftwf_out, FFTW_FORWARD, FFTW_ESTIMATE);

	levels = new float[len];
	levels_filtered = new float[len];

	memset(levels, 0, len * sizeof(float));
	memset(levels_filtered, 0, len * sizeof(float));

	in = (cmplx_float_t*)fftwf_in;
	out = (cmplx_float_t*)fftwf_out;
}

float* LIQR_Spectroscope::get_filtered_levels_buffer()
{
	return levels_filtered;
}

float* LIQR_Spectroscope::get_levels_buffer()
{
	return levels;
}

void LIQR_Spectroscope::update()
{
	memcpy(fftwf_in, parent->get_cmplx_buffer(), length * sizeof(cmplx_float_t));
	fftwf_execute(plan);

	for (int i = 0; i < length; i++)
	{
		levels[i] = 20 * log10f((out[i].real * out[i].real + out[i].imag * out[i].imag) / ((float)length * length * 256 * 256));
		levels_filtered[i] = 0.93 * levels_filtered[i] + 0.07 * levels[i];
	}
}