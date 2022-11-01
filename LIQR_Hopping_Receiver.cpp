#include "LIQR_Hopping_Receiver.h"

void* hopping_thread_fn(void* arg)
{
	LIQR_Hopping_Receiver* rec = (LIQR_Hopping_Receiver*)arg;
	while (1)
	{
		if (rec->hopping_period != 0) LIQR_sleep(rec->hopping_period);
		//rtlsdr_reset_buffer(rec->d);
		rec->current_hop++;
		rec->current_hop %= rec->hops_number;
		rtlsdr_set_center_freq(rec->d, rec->base_frequency - (rec->hops_number - 1) * MHz(1) / 2 + rec->current_hop * MHz(1));
		//printf("Current center frequency is %d\n", rtlsdr_get_center_freq(rec->d));
		//printf("Current hops is %d\n", rec->current_hop);
	}
	return 0;
}

LIQR_Hopping_Receiver::LIQR_Hopping_Receiver(uint32_t index, uint32_t sample_rate, uint32_t len, uint32_t base_freq, int hops)
{
	hops_number = hops;
	current_hop = 0;
	base_frequency = base_freq;
	length = len;

	type = LAYER_HOPPING_RECEIVER;

	rtl_buffer = new cmplx_uint8_t[length];
	buffer = new cmplx_float_t[length];
	abs_value_buffer = new float[length];

	name = "Hopping Receiver (RTL-SDR)";
	input_type = "uint8_cmplx";
	output_type = "float_cmplx";
	memset(buffer, 0, length);
	memset(abs_value_buffer, 0, length);

	rtlsdr_set_tuner_gain_mode(d, 1);

	pthread_create(&hopping_thread, NULL, hopping_thread_fn, this);
}

void LIQR_Hopping_Receiver::set_center_freq(uint32_t freq)
{
	base_frequency = freq;
}

void LIQR_Hopping_Receiver::set_hops_number(int n)
{
	hops_number = n;
	current_hop = 0;
}

