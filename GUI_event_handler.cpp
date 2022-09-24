#pragma once
#include "GUI_event_handler.h"

rtlsdr_dev_t* gui_device = nullptr;

void gui_set_device_frequency(uint32_t freq)
{
	if (gui_device != nullptr)
	{
		//rtlsdr_reset_buffer(gui_device);
		rtlsdr_set_center_freq(gui_device, freq);
	}
}