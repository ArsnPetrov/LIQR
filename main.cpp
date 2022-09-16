#include <rtl-sdr.h>
#include <stdio.h>
#include <pthread.h>
#include <fftw3.h>
#include "GUI.h"
#include "Receiver.h"

#define MHz(x) ((x) * 1000 * 1000)
#define kHz(x) ((x) * 1000)

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
	float *iq_buffer;
	float* spectre_buffer;
	Receiver *rec;

	// init sdr
	
	rtlsdr_open(&device, 0);

	window = make_window();
	liqr_set_center_freq(device, MHz(100.1));
	rtlsdr_set_sample_rate(device, kHz(2048));
	rtlsdr_set_tuner_gain_mode(device, 0);
	rtlsdr_reset_buffer(device);

	// init ui

	sdr_device_name_field->value(rtlsdr_get_device_name(0));
	tuner_gain_field->value(rtlsdr_get_tuner_gain(device) / 10);
	tabs_center_freq_field->value((double)rtlsdr_get_center_freq(device) / 1000);
	tabs_sample_rate_field->value((double)rtlsdr_get_sample_rate(device) / 1000);
	window->show();

	// init receiver

	rec = new Receiver(device, buffer_length);
	rec->listen();

	spectre_box->link_buffer((float*)rec->buffer, rec->buffer_length / 64);

	return Fl::run();
}