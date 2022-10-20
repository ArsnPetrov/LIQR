#pragma once
#include "GUI_event_handler.h"

LIQR_Spectroscope* gui_current_spectroscope = nullptr;;
LIQR_Receiver* gui_current_receiver = nullptr;
rtlsdr_dev_t* gui_device = nullptr;
SpectreDrawer* gui_current_spectre_drawer = nullptr;

void gui_set_device_frequency(uint32_t freq)
{
	if (gui_current_receiver != nullptr)
	{
		//rtlsdr_reset_buffer(gui_device);
		if (gui_current_receiver->type == LAYER_HOPPING_RECEIVER)
		{
			((LIQR_Hopping_Receiver*)gui_current_receiver)->set_center_freq(freq);
		}
		else if (gui_current_receiver->type == LAYER_RECEIVER)
		{
			gui_current_receiver->set_center_freq(freq);
		}
	}
	if (gui_current_spectre_drawer != nullptr)
	{
		//rtlsdr_reset_buffer(gui_device);
		gui_current_spectre_drawer->set_frequecny(freq);
	}
}

void gui_set_bandwidth(uint32_t freq)
{
	if (gui_device != nullptr)
	{
		//rtlsdr_reset_buffer(gui_device);
		rtlsdr_set_tuner_bandwidth(gui_device, freq);
	}
}

void gui_set_autogain(int v)
{
	if (gui_device != nullptr)
	{
		//rtlsdr_reset_buffer(gui_device);
		rtlsdr_set_tuner_gain_mode(gui_device, !v);
	}
}

void gui_set_hops_number(int n)
{
	n = 9;
	if (gui_current_receiver != nullptr)
	{
		//rtlsdr_reset_buffer(gui_device);
		if (gui_current_receiver->type == LAYER_HOPPING_RECEIVER)
		{
			((LIQR_Hopping_Receiver*)gui_current_receiver)->set_hops_number(n);

			if (gui_current_spectroscope != nullptr)
			{
				gui_current_spectroscope->change_levels_buffer_length(1024 * 8 * n / 2);
				gui_current_spectre_drawer->change_buffer(gui_current_spectroscope->get_filtered_levels_buffer(), gui_current_receiver->get_length() * n / 2);
				gui_current_spectre_drawer->set_bandwidth(MHz(1 + n));
			}
			
		}
		else if (gui_current_receiver->type == LAYER_RECEIVER)
		{
			
		}
	}
}

