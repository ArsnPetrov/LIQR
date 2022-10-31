#include <rtl-sdr.h>
#include <stdio.h>
#include <pthread.h>
#include <fftw3.h>
#include "GUI.h"
#include "LIQR_Receiver.h"
#include "LIQR_Hopping_Receiver.h"
#include "LIQR_Spectroscope.h"
#include "util.h"

int main()
{
	Fl_Double_Window* window;
	char device_name[32] = { 0 };
	int buffer_length;

	window = make_window();
	window->show();

	buffer_length = 1024;
	int hops_number = 90;
	//int hops_number = 1;

	//LIQR_Receiver* receiver = new LIQR_Receiver(0, kHz(2048), buffer_length);
	LIQR_Hopping_Receiver* receiver = new LIQR_Hopping_Receiver(0, kHz(1024), buffer_length, MHz(100), hops_number);
	
	receiver->listen();

	sdr_device_name_field->value(rtlsdr_get_device_name(0));

	LIQR_Spectroscope* spectroscope = new LIQR_Spectroscope(buffer_length);
	spectroscope->listen_to(receiver);

	gui_device = receiver->d;
	gui_current_spectre_drawer = spectre_box;
	gui_current_receiver = receiver;
	gui_current_spectroscope = spectroscope;

	spectre_box->link_buffer(spectroscope->get_filtered_levels_buffer(), buffer_length * (hops_number + 1) / 2);
	spectre_box->link_maxline(spectroscope->get_max_line_levels_buffer());
	//spectre_box->no_fftshift = true;
	spectre_box->set_bandwidth(MHz(1 + hops_number));
	spectre_box->set_frequecny(MHz(100));
	spectre_box->damage(FL_DAMAGE_ALL);

	return Fl::run();
}
