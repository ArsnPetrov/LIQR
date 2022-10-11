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

void LIQR_Spectroscope::listen_to(LIQR_Layer* l)
{
	LIQR_Layer::listen_to(l);
	if (l->type == LAYER_HOPPING_RECEIVER)
	{
		free(levels);
		free(levels_filtered);

		int hops = ((LIQR_Hopping_Receiver*)l)->hops_number;

		levels = new float[length * hops];
		levels_filtered = new float[length * hops];

		memset(levels, 0, length * hops * sizeof(float));
		memset(levels_filtered, 0, length * hops * sizeof(float));
	}
}

float* LIQR_Spectroscope::get_levels_buffer()
{
	return levels;
}

void LIQR_Spectroscope::update()
{
	memcpy(fftwf_in, parent->get_cmplx_buffer(), length * sizeof(cmplx_float_t));
	fftwf_execute(plan);

	int bias = 0;
	int hops = 1;

	if (parent->type == LAYER_HOPPING_RECEIVER)
	{
		bias = length / 2 * ((LIQR_Hopping_Receiver*)parent)->current_hop;
		hops = ((LIQR_Hopping_Receiver*)parent)->hops_number;
	}

	for (int i = 0; i < length; i++)
	{
		//printf("%f\n", levels_filtered[bias + (length / 2 + i) % length]);

		levels[bias + (length / 2 + i) % length] = 10 * log10f((out[i].real * out[i].real + out[i].imag * out[i].imag) / ((float)length * length / (hops * hops) * 256 * 256));
		levels_filtered[bias + (length / 2 + i) % length] = 0.995 * levels_filtered[bias + (length / 2 + i) % length] + 0.005 * levels[bias + (length / 2 + i) % length];

		if (isinf(levels_filtered[bias + (length / 2 + i) % length]))
		{
			levels_filtered[bias + (length / 2 + i) % length] = -50;
		}
	}
}