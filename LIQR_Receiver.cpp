#include "LIQR_Receiver.h"

void rtlsdr_callback(uint8_t* buf, uint32_t len, void* ctx)
{
	cmplx_uint8_t* buffer = (cmplx_uint8_t*)buf;
	((LIQR_Receiver*)ctx)->receive_buffer(buffer, len);
	((LIQR_Receiver*)ctx)->update();
}

static void* ___update_function(void* arg)
{
	rtlsdr_read_async(((LIQR_Receiver*)arg)->d, rtlsdr_callback, arg, 0, ((LIQR_Receiver*)arg)->get_length());

	return 0;
}

LIQR_Receiver::LIQR_Receiver(uint32_t index, uint32_t sample_rate, uint32_t len)
{
	int r;
	length = len;
	r = rtlsdr_open(&d, index);
	if (r) printf("rtlsdropen %d\n", r);
	rtlsdr_set_sample_rate(d, sample_rate);
	rtlsdr_set_tuner_gain_mode(d, 0);
	rtlsdr_set_center_freq(d, MHz(100));
	rtlsdr_reset_buffer(d);

	buffer = new cmplx_uint8_t[length];
}

LIQR_Receiver::LIQR_Receiver()
{
	length = 16 * 1024;
	rtlsdr_open(&d, 0);
	rtlsdr_set_sample_rate(d, kHz(2048));
	rtlsdr_set_tuner_gain_mode(d, 0);
	rtlsdr_set_center_freq(d, MHz(100));
	rtlsdr_reset_buffer(d);

	buffer = new cmplx_uint8_t[length];
}

LIQR_Receiver::LIQR_Receiver(int len)
{
	length = len;
	rtlsdr_open(&d, 0);
	rtlsdr_set_sample_rate(d, kHz(2048));
	rtlsdr_set_tuner_gain_mode(d, 0);
	rtlsdr_set_center_freq(d, MHz(100));
	rtlsdr_reset_buffer(d);

	buffer = new cmplx_uint8_t[length];
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
	memcpy(buffer, buf, len * sizeof(cmplx_uint8_t));
}

void LIQR_Receiver::update()
{
	if (rand() % 100 == 34) printf("ab: %d\n", get_sample(2).real);
}

cmplx_uint8_t LIQR_Receiver::get_sample(uint32_t i)
{
	return buffer[i];
}
