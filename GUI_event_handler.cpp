#pragma once
#include "GUI_event_handler.h"

rtlsdr_dev_t* gui_device = nullptr;
SpectreDrawer* gui_spectre_drawer = nullptr;

void gui_set_device_frequency(uint32_t freq)
{
	if (gui_device != nullptr)
	{
		//rtlsdr_reset_buffer(gui_device);
		rtlsdr_set_center_freq(gui_device, freq);
	}
	if (gui_spectre_drawer != nullptr)
	{
		//rtlsdr_reset_buffer(gui_device);
		gui_spectre_drawer->set_frequecny(freq);
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