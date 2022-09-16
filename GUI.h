// generated by Fast Light User Interface Designer (fluid) version 1.0308

#ifndef GUI_h
#define GUI_h
#include <FL/Fl.H>
#include "SpectreDrawer.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
extern SpectreDrawer *spectre_box;
#include <FL/Fl_Tree.H>
#include <FL/Fl_Counter.H>
extern Fl_Counter *center_freq_toggle;
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Value_Output.H>
extern Fl_Value_Output *tabs_center_freq_field;
#include <FL/Fl_Value_Input.H>
extern Fl_Value_Input *tabs_sample_rate_field;
#include <FL/Fl_Output.H>
extern Fl_Output *sdr_device_name_field;
extern Fl_Output *tuner_name_field;
extern Fl_Value_Output *xtal_freq_field;
extern Fl_Value_Output *tuner_gain_field;
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Button.H>
extern Fl_Value_Input *center_freq_field;
Fl_Double_Window* make_window();
extern Fl_Menu_Item menu_hfgdhf[];
void update_center_freq_kHz(int freq);
#endif
