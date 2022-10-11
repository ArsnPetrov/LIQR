#include "LIQR_Hopping_Receiver.h"

void* hopping_thread_fn(void* arg)
{
	LIQR_Hopping_Receiver* rec = (LIQR_Hopping_Receiver*)arg;
	while (1)
	{
		//LIQR_sleep(200);
		rec->set_center_freq(rec->base_frequency + (rec->current_hop - rec->hops_number / 2) * MHz(1));
		//rtlsdr_reset_buffer(rec->d);
		rec->current_hop++;
		rec->current_hop %= rec->hops_number;
		printf("Current hops is %d\n", rec->current_hop);
	}
	return 0;
}

LIQR_Hopping_Receiver::LIQR_Hopping_Receiver(uint32_t index, uint32_t sample_rate, uint32_t len, uint32_t base_freq, int hops)
{
	hops_number = hops;
	current_hop = 0;
	base_frequency = base_freq;

	type = LAYER_HOPPING_RECEIVER;

	//memset(rtl_buffer, 0, section_length);
	memset(buffer, 0, length);
	memset(abs_value_buffer, 0, length);

	rtlsdr_set_tuner_gain_mode(d, 0);

	pthread_create(&hopping_thread, NULL, hopping_thread_fn, this);

	//current_hop++;
	//current_hop %= hops_number;
}