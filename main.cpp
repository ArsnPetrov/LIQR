#include <rtl-sdr.h>
#include <stdio.h>
#include <pthread.h>
#include <fftw3.h>
#include "GUI.h"
#include "LIQR_Receiver.h"
#include "LIQR_Spectroscope.h"
#include "util.h"

int buffer_length = 1024;

int liqr_set_center_freq(rtlsdr_dev_t* dev, uint32_t freq)
{
	center_freq_field->value((double)freq / 1000);
	center_freq_toggle->value((double)freq / 1000);
	tabs_center_freq_field->value((double)freq / 1000);
	return rtlsdr_set_center_freq(dev, freq);
}

int main()
{
	Fl_Double_Window* window;
	rtlsdr_dev_t* device;
	char device_name[32] = { 0 };

	// init receiver

	LIQR_Receiver *receiver = new LIQR_Receiver(0, kHz(2048), 1024);
	receiver->listen();

	// init ui

	window = make_window();
	// sdr_device_name_field->value(rtlsdr_get_device_name(0));
	// tuner_gain_field->value(rtlsdr_get_tuner_gain(rec->d) / 10);
	// tabs_center_freq_field->value((double)rtlsdr_get_center_freq(rec->d) / 1000);
	// tabs_sample_rate_field->value((double)rtlsdr_get_sample_rate(rec->d) / 1000);
	window->show();

	//spectre_box->link_buffer((float*)rec->buffer, rec->buffer_length / 64);

	LIQR_Spectroscope<cmplx_uint8_t> *spectroscope = new LIQR_Spectroscope<cmplx_uint8_t>();
	spectroscope->listen_to(receiver);

	return Fl::run();
}
