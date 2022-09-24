#include <rtl-sdr.h>
#include <stdio.h>
#include <pthread.h>
#include <fftw3.h>
#include "GUI.h"
#include "LIQR_Receiver.h"
#include "LIQR_Spectroscope.h"
#include "util.h"

int main()
{
	Fl_Double_Window* window;
	char device_name[32] = { 0 };
	int buffer_length;

	window = make_window();
	window->show();

	buffer_length = 2048;

	LIQR_Receiver* receiver = new LIQR_Receiver(0, kHz(2048), buffer_length);
	receiver->listen();

	gui_device = receiver->d;
	gui_spectre_drawer = spectre_box;

	sdr_device_name_field->value(rtlsdr_get_device_name(0));

	LIQR_Spectroscope* spectroscope = new LIQR_Spectroscope(buffer_length);
	spectroscope->listen_to(receiver);

	spectre_box->link_buffer(spectroscope->get_filtered_levels_buffer(), buffer_length);
	
	spectre_box->damage(FL_DAMAGE_ALL);

	return Fl::run();
}
