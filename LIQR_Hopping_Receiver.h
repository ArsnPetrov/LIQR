#pragma once
#include "LIQR_Receiver.h"
#include "util.h"

class LIQR_Hopping_Receiver :
	public LIQR_Receiver
{
	pthread_t hopping_thread;

public:
	uint32_t base_frequency;
	int current_hop;
	int hops_number;
	int hopping_period; // [ms]

	/**
		Receiver's constructor. Opens and RTL-SDR device with given index. Sets the sample
		rate, buffer size in accordance with given parameters. Resets RTL-SDR's buffer.

		/param index id of chosen of rtl-sdr
		/param sample_rate receiver's sample rate; to be set considering rtl-sdr's limitations
		/param len length of a received block
		/param hops number of frequency hops. Resulting bandwidth will be 2 MHz * hops
	*/
	LIQR_Hopping_Receiver(uint32_t index, uint32_t sample_rate, uint32_t len, uint32_t base_freq, int hops);

	/**
		Resets Hopping Receiver's base frequency

		/param freq new center frequency
	*/
	void set_center_freq(uint32_t freq);

	void set_hops_number(int n);
};