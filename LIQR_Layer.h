#pragma once
#include <vector>
#include <pthread.h>
#include <fftw3.h>
#include <cmath>
#include "util.h"

typedef enum {
	LAYER_BASE, LAYER_RECEIVER, LAYER_SPECTROSCOPE
} layer_type_id;

class LIQR_Layer
{
protected:
	cmplx_float_t* buffer;

	LIQR_Layer* parent;

	uint32_t length; // length of the layer in samples
	uint32_t sample_rate; // serves mainly for informative purposes, except for receiving/playing cases

	pthread_t thread;

	float* abs_value_buffer;

	std::vector<LIQR_Layer*> children;

public:
	layer_type_id type;

	LIQR_Layer();
	LIQR_Layer(int len);

	/**
		Adds the layer l to the list of descendants. Adds the l's update()
		method to this layer's call_down() queue.

		Should not be called directly.

		/param l layer to make a descendant
	*/
	void _add_listener(LIQR_Layer* l);

	/**
		Adds this layer as a descendant of layer l. Gains access to
		layer l's buffer. Locks this function's update() method to l's
		call_down().

		/param l layer to descend from
	*/
	void listen_to(LIQR_Layer* l);

	/**
		Calls update() method of every descendant layer
	*/
	void call_down();

	/**
		Main signal processing function. For streamed inputs (SDR)
		usually runs in a separate thread.
	*/
	void update();

	void calculate_abs_buffer();

	uint32_t get_length();

	cmplx_float_t get_sample(uint32_t i);

	fftwf_complex* get_fftwf_buffer();

	cmplx_float_t* get_cmplx_buffer();

	float* get_abs_buffer();
};


