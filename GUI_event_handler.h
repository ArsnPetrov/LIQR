#pragma once
#include <rtl-sdr.h>
#include <stdio.h>
#include "LIQR_Receiver.h"
#include "LIQR_Hopping_Receiver.h"
#include "LIQR_Spectroscope.h"
#include "SpectreDrawer.h"
#include "util.h"

extern SpectreDrawer* gui_current_spectre_drawer;
extern LIQR_Spectroscope* gui_current_spectroscope;
extern LIQR_Receiver* gui_current_receiver;
extern rtlsdr_dev_t* gui_device;
extern SpectreDrawer* gui_current_spectre_drawer;
extern void gui_set_device_frequency(uint32_t freq);
extern void gui_set_bandwidth(uint32_t freq);
extern void gui_set_autogain(int v);
extern void gui_set_hops_number(int n);