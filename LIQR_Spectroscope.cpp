#include "LIQR_Spectroscope.h"
#include "LIQR_Receiver.h"

LIQR_Spectroscope::LIQR_Spectroscope(uint32_t len)
{
	length = len;
	type = LAYER_SPECTROSCOPE;

	active = true;

	fftwf_in = fftwf_alloc_complex(length);
	fftwf_out = fftwf_alloc_complex(length);
	plan = fftwf_plan_dft_1d(length, fftwf_in, fftwf_out, FFTW_FORWARD, FFTW_ESTIMATE);

	levels = new float[len];
	levels_filtered = new float[len];
	levels_max_line = new float[len];

	for (int i = 0; i < length; i++)
	{
		levels[i] = -150;
		levels_filtered[i] = -150;
		levels_max_line[i] = -150;
	}

	in = (cmplx_float_t*)fftwf_in;
	out = (cmplx_float_t*)fftwf_out;
}

float* LIQR_Spectroscope::get_filtered_levels_buffer()
{
	return levels_filtered;
}

float* LIQR_Spectroscope::get_max_line_levels_buffer()
{
	return levels_max_line;
}

void LIQR_Spectroscope::listen_to(LIQR_Layer* l)
{
	LIQR_Layer::listen_to(l);
	if (l->type == LAYER_HOPPING_RECEIVER)
	{
		free(levels);
		free(levels_filtered);
		free(levels_max_line);

		int hops = ((LIQR_Hopping_Receiver*)l)->hops_number;

		levels = new float[length * hops];
		levels_filtered = new float[length * hops];
		levels_max_line = new float[length * hops];

		for (int i = 0; i < length * hops; i++)
		{
			levels[i] = -150;
			levels_filtered[i] = -150;
			levels_max_line[i] = -150;
		}
	}
}

float* LIQR_Spectroscope::get_levels_buffer()
{
	return levels;
}

void LIQR_Spectroscope::update()
{
	if (!active) return;

	memcpy(fftwf_in, parent->get_cmplx_buffer(), length * sizeof(cmplx_float_t));
	fftwf_execute(plan);

	int bias = 0;
	int hops = 1;
	double blackman = 1;

	if (parent->type == LAYER_HOPPING_RECEIVER)
	{
		bias = length / 2 * ((LIQR_Hopping_Receiver*)parent)->current_hop;
		hops = ((LIQR_Hopping_Receiver*)parent)->hops_number;
	}

	//if (bias != 0) return;

	for (int i = 0; i < length; i++)
	{
		if (hops != 1)
		{
			blackman = 0.42 - 0.5 * cos(2 * PI * i / (length - 1)) + 0.08 * cos(4 * PI * i / (length - 1));
		}
		//printf("%f\n", levels_filtered[bias + (length / 2 + i) % length]);
		int _j = (length / 2 + i) % length;
		levels[bias + i] = 0.9 * levels[bias + i] + 1 * log10f((out[_j].real * out[_j].real + out[_j].imag * out[_j].imag) / ((float)length * length / (hops * hops) * 256 * 256));
		levels_filtered[bias + i] = 0.98 * levels_filtered[bias + i] + 0.02 * levels[bias + i];
		//levels_filtered[bias + i] = -100;
		if (levels_filtered[bias + i] != 0 && levels_filtered[bias + i] > levels_max_line[bias + i]) levels_max_line[bias + i] = levels_filtered[bias + i];

		if (isinf(levels_filtered[bias + i]))
		{
			levels_filtered[bias + i] = -100;
		}
	}
}

void LIQR_Spectroscope::change_levels_buffer_length(int l)
{
	free(levels);
	free(levels_filtered);
	free(levels_max_line);

	levels = new float[l];
	levels_filtered = new float[l];
	levels_max_line = new float[l];

	memset(levels, -150, l * sizeof(float));
	memset(levels_filtered, -150, l * sizeof(float));
	memset(levels_max_line, -150, l * sizeof(float));
}
