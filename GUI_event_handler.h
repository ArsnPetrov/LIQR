#pragma once
#include <rtl-sdr.h>
#include <stdio.h>

extern rtlsdr_dev_t* gui_device;
extern void gui_set_device_frequency(uint32_t freq);