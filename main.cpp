#include <rtl-sdr.h>
#include <stdio.h>
#include <pthread.h>
#include <fftw3.h>
#include "GUI.h"
#include "LIQR_Receiver.h"
#include "LIQR_Hopping_Receiver.h"
#include "LIQR_Spectroscope.h"
#include "util.h"

void add_level_to_tree(LIQR_Layer *l, std::string str)
{
	layers_tree->add((str + l->name).c_str());

	for (int i = 0; i < l->children.size(); i++)
	{
		add_level_to_tree(l->children[i], str + l->name.c_str() + "/");
	}
}

void update_layer_panel()
{
	layer_name_field->value(gui_current_layer->name.c_str());
	layer_input_type_field->value(gui_current_layer->input_type.c_str());
	layer_output_type_field->value(gui_current_layer->output_type.c_str());
	layer_output_buffer_size->value(gui_current_layer->get_length());
	layer_sample_rate->value(gui_current_layer->sample_rate / 1000);
}

int main()
{
	Fl_Double_Window* window;
	char device_name[32] = { 0 };
	int buffer_length;

	window = make_window();
	window->show();

	buffer_length = 1024;
	int hops_number = 90;

	// LIQR setup

	//LIQR_Receiver* receiver = new LIQR_Receiver(0, kHz(2048), buffer_length);
	LIQR_Hopping_Receiver* receiver = new LIQR_Hopping_Receiver(0, kHz(1024), buffer_length, MHz(100), hops_number);
	
	receiver->listen();

	sdr_device_name_field->value(rtlsdr_get_device_name(0));

	LIQR_Spectroscope* spectroscope = new LIQR_Spectroscope(buffer_length);
	spectroscope->listen_to(receiver);

	// GUI

	gui_device = receiver->d;
	gui_current_spectre_drawer = spectre_box;
	gui_current_receiver = receiver;
	gui_current_spectroscope = spectroscope;
	gui_current_layer = receiver;

	update_layer_panel();

	spectre_box->link_buffer(spectroscope->get_filtered_levels_buffer(), buffer_length * (hops_number + 1) / 2);
	spectre_box->link_maxline(spectroscope->get_max_line_levels_buffer());
	spectre_box->set_bandwidth(MHz(1 + hops_number));
	spectre_box->set_frequecny(MHz(100));
	spectre_box->damage(FL_DAMAGE_ALL);

	layers_tree->clear();
	layers_tree->showroot(0);
	layers_tree->item_labelsize(11);
	
	add_level_to_tree(receiver, "");

	return Fl::run();
}
