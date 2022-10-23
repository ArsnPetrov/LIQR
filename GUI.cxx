// generated by Fast Light User Interface Designer (fluid) version 1.0308

#include "GUI.h"

Fl_Menu_Item menu_hfgdhf[] = {
 {"\320\244\320\260\320\271\320\273", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {"\320\236\321\202\320\272\321\200\321\213\321\202\321\214 I/Q \321\204\320\
\260\320\271\320\273 (Ctrl-O)", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {"\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214 I/Q (Ctrl-R)", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {"\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\
\320\265", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0}
};

Fl_Value_Output *tabs_center_freq_field=(Fl_Value_Output *)0;

static void cb_(Fl_Value_Input* o, void*) {
  update_bandwidth_kHz(o->value());
}

Fl_Value_Input *tabs_sample_rate_field=(Fl_Value_Input *)0;

Fl_Output *sdr_device_name_field=(Fl_Output *)0;

Fl_Output *tuner_name_field=(Fl_Output *)0;

Fl_Value_Output *tuner_gain_field=(Fl_Value_Output *)0;

static void cb_1(Fl_Check_Button* o, void*) {
  gui_set_autogain(o->value());
}

Fl_Value_Input *freq_hop_step_field=(Fl_Value_Input *)0;

static void cb_freq_hop_step_field(Fl_Value_Input* o, void*) {
  update_bandwidth_kHz(o->value());
}

Fl_Value_Input *hop_steps_field=(Fl_Value_Input *)0;

static void cb_hop_steps_field(Fl_Value_Input* o, void*) {
  hop_bandwidth_field->value((o->value() + 1) * 1000);
gui_set_hops_number(o->value());
}

Fl_Value_Input *hop_bandwidth_field=(Fl_Value_Input *)0;

static void cb_hop_bandwidth_field(Fl_Value_Input* o, void*) {
  hop_steps_field->value(o->value() / 1000 - 1);
}

Fl_Value_Input *hop_period_field=(Fl_Value_Input *)0;

static void cb_hop_period_field(Fl_Value_Input* o, void*) {
  update_bandwidth_kHz(o->value());
}

static void cb_2(Fl_Check_Button*, void*) {
  //freq_hop_step_field->active() ? freq_hop_step_field->deactivate() : freq_hop_step_field->activate();
hop_steps_field->active() ? hop_steps_field->deactivate() : hop_steps_field->activate();
hop_bandwidth_field->active() ? hop_bandwidth_field->deactivate() : hop_bandwidth_field->activate();
hop_period_field->active() ? hop_period_field->deactivate() : hop_period_field->activate();
}

SpectreDrawer *spectre_box=(SpectreDrawer *)0;

Fl_Value_Input *center_freq_field=(Fl_Value_Input *)0;

static void cb_center_freq_field(Fl_Value_Input* o, void*) {
  update_center_freq_kHz(o->value());
}

Fl_Counter *center_freq_toggle=(Fl_Counter *)0;

static void cb_center_freq_toggle(Fl_Counter* o, void*) {
  update_center_freq_kHz(o->value());
}

Fl_Double_Window* make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(705, 574, "LIQR - Layered I/Q Receiver");
    w = o; if (w) {/* empty */}
    o->color(FL_DARK1);
    o->labelsize(12);
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 970, 20, "hfgdhf");
      o->menu(menu_hfgdhf);
    } // Fl_Menu_Bar* o
    { Fl_Tabs* o = new Fl_Tabs(10, 410, 490, 155);
      { Fl_Group* o = new Fl_Group(15, 430, 485, 105, "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \
\320\277\321\200\320\270\321\221\320\274\320\260");
        o->labelsize(13);
        { tabs_center_freq_field = new Fl_Value_Output(230, 440, 260, 20, "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\
\260\321\217 \321\207\320\260\321\201\321\202\320\276\321\202\320\260, \320\
\272\320\223\321\206::");
          tabs_center_freq_field->labelsize(12);
          tabs_center_freq_field->textsize(12);
        } // Fl_Value_Output* tabs_center_freq_field
        { Fl_Value_Input* o = new Fl_Value_Input(230, 490, 260, 20, "\320\237\320\276\320\273\320\276\321\201\320\260 \320\277\321\200\320\276\
\320\277\321\203\321\201\320\272\320\260\320\275\320\270\321\217, \320\272\
\320\223\321\206:");
          o->labelsize(12);
          o->maximum(2000);
          o->value(2000);
          o->textsize(12);
          o->callback((Fl_Callback*)cb_);
        } // Fl_Value_Input* o
        { tabs_sample_rate_field = new Fl_Value_Input(230, 465, 260, 20, "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\264\320\270\
\321\201\320\272\321\200\320\265\321\202\320\270\320\267\320\260\321\206\320\
\270\320\270, \320\272\320\223\321\206:");
          tabs_sample_rate_field->labelsize(12);
          tabs_sample_rate_field->maximum(2000);
          tabs_sample_rate_field->value(2400);
          tabs_sample_rate_field->textsize(12);
        } // Fl_Value_Input* tabs_sample_rate_field
        { Fl_Input* o = new Fl_Input(230, 515, 260, 20, "\320\244\320\260\320\271\320\273 \320\264\320\273\321\217 \320\267\320\260\
\320\277\320\270\321\201\320\270:");
          o->labelsize(12);
          o->textsize(12);
          o->deactivate();
        } // Fl_Input* o
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(15, 430, 485, 135, "\320\236\320\261 SDR");
        o->labelsize(12);
        o->hide();
        { sdr_device_name_field = new Fl_Output(230, 440, 260, 20, "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\203\
\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260:");
          sdr_device_name_field->labelsize(12);
          sdr_device_name_field->textsize(12);
        } // Fl_Output* sdr_device_name_field
        { tuner_name_field = new Fl_Output(230, 465, 260, 20, "\320\242\320\270\320\277 \321\202\321\216\320\275\320\265\321\200\320\260:");
          tuner_name_field->labelsize(12);
          tuner_name_field->textsize(12);
        } // Fl_Output* tuner_name_field
        { tuner_gain_field = new Fl_Value_Output(230, 490, 260, 20, "\320\243\321\201\320\270\320\273\320\265\320\275\320\270\320\265 \321\202\
\321\216\320\275\320\265\321\200\320\260, \320\264\320\221:");
          tuner_gain_field->labelsize(12);
          tuner_gain_field->textsize(12);
        } // Fl_Value_Output* tuner_gain_field
        { Fl_Check_Button* o = new Fl_Check_Button(230, 515, 15, 15, "\320\220\320\262\321\202\320\276\320\272\320\276\320\275\321\202\321\200\320\
\276\320\273\321\214 \321\203\321\201\320\270\320\273\320\265\320\275\320\270\
\321\217");
          o->down_box(FL_DOWN_BOX);
          o->labelsize(12);
          o->callback((Fl_Callback*)cb_1);
          o->align(Fl_Align(FL_ALIGN_LEFT));
        } // Fl_Check_Button* o
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(10, 430, 490, 130, "\320\241\320\272\320\260\320\275\320\270\321\200\321\203\321\216\321\211\320\
\270\320\271 \320\277\321\200\320\270\321\221\320\274");
        o->labelsize(13);
        o->hide();
        { freq_hop_step_field = new Fl_Value_Input(230, 460, 260, 20, "\320\250\320\260\320\263 \320\277\320\265\321\200\320\265\321\201\321\202\
\321\200\320\276\320\271\320\272\320\270, \320\272\320\223\321\206:");
          freq_hop_step_field->labelsize(12);
          freq_hop_step_field->maximum(2000);
          freq_hop_step_field->value(1000);
          freq_hop_step_field->textsize(12);
          freq_hop_step_field->callback((Fl_Callback*)cb_freq_hop_step_field);
          freq_hop_step_field->deactivate();
        } // Fl_Value_Input* freq_hop_step_field
        { hop_steps_field = new Fl_Value_Input(230, 485, 260, 20, "\320\250\320\260\320\263\320\276\320\262 \320\277\320\265\321\200\320\265\
\321\201\321\202\321\200\320\276\320\271\320\272\320\270:");
          hop_steps_field->labelsize(12);
          hop_steps_field->maximum(2000);
          hop_steps_field->value(9);
          hop_steps_field->textsize(12);
          hop_steps_field->callback((Fl_Callback*)cb_hop_steps_field);
          hop_steps_field->deactivate();
        } // Fl_Value_Input* hop_steps_field
        { hop_bandwidth_field = new Fl_Value_Input(230, 510, 260, 20, "\320\250\320\270\321\200\320\270\320\275\320\260 \320\277\320\276\320\273\
\320\276\321\201\321\213 \321\201\320\272\320\260\320\275\320\270\321\200\320\
\276\320\262\320\260\320\275\320\270\321\217, \320\272\320\223\321\206:");
          hop_bandwidth_field->labelsize(12);
          hop_bandwidth_field->minimum(2000);
          hop_bandwidth_field->maximum(200000);
          hop_bandwidth_field->value(20000);
          hop_bandwidth_field->textsize(12);
          hop_bandwidth_field->callback((Fl_Callback*)cb_hop_bandwidth_field);
          hop_bandwidth_field->deactivate();
        } // Fl_Value_Input* hop_bandwidth_field
        { hop_period_field = new Fl_Value_Input(230, 535, 260, 20, "\320\237\320\265\321\200\320\270\320\276\320\264 \320\277\320\265\321\200\
\320\265\321\201\321\202\321\200\320\276\320\271\320\272\320\270, \320\274\
\321\201:");
          hop_period_field->labelsize(12);
          hop_period_field->minimum(2000);
          hop_period_field->maximum(200000);
          hop_period_field->value(100);
          hop_period_field->textsize(12);
          hop_period_field->callback((Fl_Callback*)cb_hop_period_field);
          hop_period_field->deactivate();
        } // Fl_Value_Input* hop_period_field
        { Fl_Check_Button* o = new Fl_Check_Button(230, 440, 15, 15, "\320\241\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\321\
\202\321\214 \320\264\320\270\320\260\320\277\320\260\320\267\320\276\320\275");
          o->down_box(FL_DOWN_BOX);
          o->labelsize(12);
          o->callback((Fl_Callback*)cb_2);
          o->align(Fl_Align(FL_ALIGN_LEFT));
        } // Fl_Check_Button* o
        o->end();
      } // Fl_Group* o
      o->end();
    } // Fl_Tabs* o
    { Fl_Tabs* o = new Fl_Tabs(10, 30, 685, 310);
      { spectre_box = new SpectreDrawer(10, 50, 685, 290, "\320\241\320\237\320\225\320\232\320\242\320\240");
        spectre_box->box(FL_BORDER_BOX);
        spectre_box->color((Fl_Color)24);
        spectre_box->selection_color(FL_BACKGROUND_COLOR);
        spectre_box->labeltype(FL_NORMAL_LABEL);
        spectre_box->labelfont(0);
        spectre_box->labelsize(10);
        spectre_box->labelcolor(FL_LIGHT3);
        spectre_box->align(Fl_Align(FL_ALIGN_CENTER));
        spectre_box->when(FL_WHEN_RELEASE);
        Fl_Group::current()->resizable(spectre_box);
        spectre_box->window()->hotspot(spectre_box);
      } // SpectreDrawer* spectre_box
      o->end();
    } // Fl_Tabs* o
    { Fl_Group* o = new Fl_Group(10, 345, 685, 65);
      { Fl_Light_Button* o = new Fl_Light_Button(185, 350, 110, 20, "\320\227\320\220\320\237\320\230\320\241\320\254 I/Q (0 MB)");
        o->selection_color((Fl_Color)89);
        o->labelsize(10);
        o->deactivate();
      } // Fl_Light_Button* o
      { Fl_Button* o = new Fl_Button(65, 350, 60, 20, "\320\237\320\243\320\241\320\232");
        o->tooltip("start");
        o->labelsize(10);
        o->deactivate();
      } // Fl_Button* o
      { Fl_Button* o = new Fl_Button(125, 350, 60, 20, "\320\241\320\242\320\236\320\237");
        o->labelsize(10);
        o->deactivate();
      } // Fl_Button* o
      { Fl_Light_Button* o = new Fl_Light_Button(10, 350, 55, 20, "\320\220\320\243\320\224\320\230\320\236");
        o->selection_color((Fl_Color)2);
        o->labelsize(10);
        o->deactivate();
      } // Fl_Light_Button* o
      { center_freq_field = new Fl_Value_Input(185, 375, 110, 20);
        center_freq_field->labeltype(FL_NO_LABEL);
        center_freq_field->labelsize(11);
        center_freq_field->value(100000);
        center_freq_field->textsize(12);
        center_freq_field->callback((Fl_Callback*)cb_center_freq_field);
      } // Fl_Value_Input* center_freq_field
      { Fl_Counter* o = center_freq_toggle = new Fl_Counter(10, 375, 170, 20, "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\
\260\321\217 \321\207\320\260\321\201\321\202\320\276\321\202\320\260, \320\
\272\320\223\321\206");
        center_freq_toggle->labelsize(12);
        center_freq_toggle->minimum(0);
        center_freq_toggle->maximum(1.8e+06);
        center_freq_toggle->step(0);
        center_freq_toggle->value(100000);
        center_freq_toggle->textsize(12);
        center_freq_toggle->callback((Fl_Callback*)cb_center_freq_toggle);
        o->step(100);
        o->lstep(1000);
      } // Fl_Counter* center_freq_toggle
      { Fl_Group* o = new Fl_Group(300, 350, 395, 45);
        o->end();
        Fl_Group::current()->resizable(o);
      } // Fl_Group* o
      o->end();
      Fl_Group::current()->resizable(o);
    } // Fl_Group* o
    o->end();
  } // Fl_Double_Window* o
  return w;
}

void update_center_freq_kHz(int freq) {
  center_freq_field->value(freq);
  center_freq_toggle->value(freq);
  tabs_center_freq_field->value(freq);
  gui_set_device_frequency(freq * 1000);
}

void update_bandwidth_kHz(int freq) {
  gui_set_bandwidth(freq * 1000);
}
