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
	(layers_tree->find_item((str + l->name).c_str()))->user_data(l);

	for (int i = 0; i < l->children.size(); i++)
	{
		add_level_to_tree(l->children[i], str + l->name.c_str() + "/");
	}
}

void update_layer_panel()
{
	if (gui_current_layer == nullptr) return;

	layer_name_field->redraw_label();
	layer_name_field->value(gui_current_layer->name.c_str());
	layer_input_type_field->value(gui_current_layer->input_type.c_str());
	layer_output_type_field->value(gui_current_layer->output_type.c_str());
	layer_output_buffer_size->value(gui_current_layer->get_length());
	layer_sample_rate->value(gui_current_layer->sample_rate / 1000);
	if (gui_current_layer->parent != nullptr) layer_input_buffer_size->value(gui_current_layer->parent->get_length());
}

void update_new_layer_layers_list()
{
	if (new_layer_parent_choice != nullptr)
	{
		for (int i = 0; i < gui_layer_list->size(); i++)
		{
			new_layer_parent_choice->clear();
			new_layer_parent_choice->add(gui_layer_list->at(i)->name.c_str());
		}
	}
}

void tree_callback(Fl_Widget* w, void* data)
{
	Fl_Tree_Item* selected_item;
	selected_item = layers_tree->first_selected_item();
	if (selected_item == 0)
	{
		return;
	}
	gui_current_layer = (LIQR_Layer*)selected_item->user_data();
	printf("Layer name: %s\n", gui_current_layer->name.c_str());
	update_layer_panel();
}

int main()
{
	// receiver parameters

	int buffer_length = 6400;
	int hops_number = 1;

	// LIQR setup
	
	std::vector<LIQR_Layer*> layers;
	gui_layer_list = &layers;

	LIQR_Receiver* receiver = new LIQR_Receiver(0, kHz(2048), buffer_length);
	receiver->listen();

	LIQR_Spectroscope* spectroscope = new LIQR_Spectroscope(buffer_length);
	spectroscope->listen_to(receiver);

	//LIQR_Hopping_Receiver *hopping_receiver = new LIQR_Hopping_Receiver(0, kHz(2048), buffer_length, MHz(100), hops_number);
	//hopping_receiver->listen();



	// GUI

	Fl_Double_Window* window;

	window = make_window();
	window->show();

	gui_device = receiver->d;
	gui_current_spectre_drawer = spectre_box;
	gui_current_receiver = receiver;
	gui_current_spectroscope = spectroscope;
	gui_current_layer = receiver;

	sdr_device_name_field->value(rtlsdr_get_device_name(0));

	update_layer_panel();

	spectre_box->link_buffer(spectroscope->get_filtered_levels_buffer(), buffer_length / 2 * (hops_number + 1));
	spectre_box->link_maxline(spectroscope->get_max_line_levels_buffer());
	spectre_box->set_bandwidth(MHz(1 + hops_number));
	spectre_box->set_frequecny(MHz(100));
	spectre_box->damage(FL_DAMAGE_ALL);

	layers_tree->callback(tree_callback);
	layers_tree->clear();
	layers_tree->showroot(0);
	layers_tree->item_labelsize(12);
	
	add_level_to_tree(receiver, "");

	return Fl::run();
}
