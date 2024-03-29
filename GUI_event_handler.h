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
extern LIQR_Layer* gui_current_layer;
extern std::vector<LIQR_Layer*>* gui_layer_list;
extern void gui_set_device_frequency(uint32_t freq);
extern void gui_set_bandwidth(uint32_t freq);
extern void gui_set_autogain(int v);
extern void gui_set_hops_number(int n);
extern void gui_start_spectre();
extern void gui_stop_spectre();
extern void gui_set_hopping_period(int t);
extern void gui_add_layer(const char* option);