#pragma once
#include "LIQR_Layer.h"
#include "util.h"
#include <rtl-sdr.h>

class LIQR_Receiver : public LIQR_Layer<cmplx_uint8_t>
{
public:
	rtlsdr_dev_t* d; // main device to listen from

	/**
		Receiver's constructor. Opens and RTL-SDR device with given index. Sets the sample
		rate, buffer size in accordance with given parameters. Resets RTL-SDR's buffer.

		/param index id of chosen of rtl-sdr
		/param sample_rate receiver's sample rate; to be set considering rtl-sdr's limitations
		/param len length of a received block
	*/
	LIQR_Receiver(uint32_t index, uint32_t sample_rate, uint32_t len);

	/**
		Default sample rate — 2048 kHzm, len — 16 * 1024
	*/
	LIQR_Receiver();

	LIQR_Receiver(int len);

	/**
		Creates a separate thread. Reads I/Q data asyncronoulsy from Receiver's device *d.
		Data reading parameters are specified by sample_rate and len Receiver's properties.
		Leads to periodic (with frequency being equal to sample_rate) execution of update() 
		method of this layer and all subsequent descendant layers.
	*/
	void listen();

	/**
		Resets Receiver's center frequency

		/param freq new center frequency
	*/
	void set_center_freq(uint32_t freq);

	/**
		Copies the data from *buf to Receiver's buffer

		/param buf buffer of complex samples
		/param len length of the bufffer in samples
	*/
	void receive_buffer(cmplx_uint8_t* buf, uint32_t len);

	virtual void update();

	cmplx_uint8_t get_sample(uint32_t i);
};

