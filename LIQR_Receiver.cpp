#include "LIQR_Receiver.h"

void rtlsdr_callback(uint8_t* buf, uint32_t len, void* ctx)
{
	cmplx_uint8_t* buffer = (cmplx_uint8_t*)buf;
	((LIQR_Receiver*)ctx)->receive_buffer(buffer, len);
	((LIQR_Receiver*)ctx)->update();
}

LIQR_Receiver::LIQR_Receiver(uint32_t index, uint32_t sample_rate, uint32_t len)
{
	type = LAYER_RECEIVER;
	length = len;
	d = nullptr;

	int r;
	r = rtlsdr_open(&d, index);
	if (r)
	{
		printf("rtlsdropen %d\n", r);
	}
	rtlsdr_set_sample_rate(d, sample_rate);
	rtlsdr_set_tuner_gain_mode(d, 0);
	rtlsdr_set_center_freq(d, MHz(100));
	//rtlsdr_set_testmode(d, 1);
	rtlsdr_reset_buffer(d);

	rtl_buffer = new cmplx_uint8_t[length];
	buffer = new cmplx_float_t[length];
	abs_value_buffer = new float[length];
}

static void* ___update_function(void* arg)
{
	rtlsdr_read_async(((LIQR_Receiver*)arg)->d, rtlsdr_callback, arg, 0, ((LIQR_Receiver*)arg)->get_length() * 2);

	return 0;
}

void LIQR_Receiver::listen()
{
	pthread_create(&thread, 0, ___update_function, this);
}

void LIQR_Receiver::set_center_freq(uint32_t freq)
{
	rtlsdr_set_center_freq(d, freq);
}

void LIQR_Receiver::receive_buffer(cmplx_uint8_t* buf, uint32_t len)
{
	memcpy(rtl_buffer, buf, len * sizeof(uint8_t));
}

void LIQR_Receiver::update()
{
	for (uint32_t i = 0; i < length; i++)
	{
		buffer[i].real = static_cast<float>((rtl_buffer[i]).real) - 128;
		buffer[i].imag = static_cast<float>((rtl_buffer[i]).imag) - 128;
	}
	calculate_abs_buffer();
	call_down();
}

cmplx_float_t LIQR_Receiver::get_sample(uint32_t i)
{
	return buffer[i];
}
