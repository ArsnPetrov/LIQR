#pragma once
#include <vector>
#include <pthread.h>
#include "util.h"

template<typename buf_t>
class LIQR_Layer
{
	LIQR_Layer* parent;
	std::vector<LIQR_Layer*> children;

protected:
	buf_t* buffer;

	uint32_t length; // length of the layer in samples of buf_t
	uint32_t sample_rate; // serves mainly for informative purposes, except for receiving/playing cases

	pthread_t thread;

	/**
		Adds the layer l to the list of descendants. Adds the l's update()
		method to this layer's call_down() queue.

		Should not be called directly.

		/param l layer to make a descendant
	*/
	void _add_listener(LIQR_Layer* l);

public:
	LIQR_Layer();
	LIQR_Layer(int length);

	/**
		Adds this layer as a descendant of layer l. Gains access to
		layer l's buffer. Locks this function's update() method to l's
		call_down().

		/param l layer to descend from
	*/
	void listen_to(LIQR_Layer* l);

	/**
		Calls update() method of every descendant Layer
	*/
	void call_down();

	/**
		Main signal processing function. For streamed inputs (SDR)
		usually runs in a separate thread.
	*/
	virtual void update();

	uint32_t get_length();

	buf_t get_sample(uint32_t i);
};