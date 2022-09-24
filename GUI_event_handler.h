#pragma once
#include <rtl-sdr.h>
#include <stdio.h>
#include "SpectreDrawer.h"

extern rtlsdr_dev_t* gui_device;
extern SpectreDrawer* gui_spectre_drawer;
extern void gui_set_device_frequency(uint32_t freq);
extern void gui_set_bandwidth(uint32_t freq);