// generated by Fast Light User Interface Designer (fluid) version 1.0308

#include "GUI.h"

Fl_Menu_Item menu_hfgdhf[] = {
 {"\320\244\320\260\320\271\320\273", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {"\320\236\321\202\320\272\321\200\321\213\321\202\321\214 I/Q \321\204\320\
\260\320\271\320\273 (Ctrl-O)", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {"\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214 I/Q (Ctrl-R)", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};

SpectreDrawer *spectre_box=(SpectreDrawer *)0;

Fl_Counter *center_freq_toggle=(Fl_Counter *)0;

static void cb_center_freq_toggle(Fl_Counter* o, void*) {
  update_center_freq_kHz(o->value());
}

Fl_Value_Output *tabs_center_freq_field=(Fl_Value_Output *)0;

static void cb_(Fl_Value_Input* o, void*) {
  update_bandwidth_kHz(o->value());
}

Fl_Value_Input *tabs_sample_rate_field=(Fl_Value_Input *)0;

Fl_Output *sdr_device_name_field=(Fl_Output *)0;

Fl_Output *tuner_name_field=(Fl_Output *)0;

Fl_Value_Output *xtal_freq_field=(Fl_Value_Output *)0;

Fl_Value_Output *tuner_gain_field=(Fl_Value_Output *)0;

Fl_Value_Input *center_freq_field=(Fl_Value_Input *)0;

static void cb_center_freq_field(Fl_Value_Input* o, void*) {
  update_center_freq_kHz(o->value());
}

Fl_Double_Window* make_window() {
  Fl_Double_Window* w;
  { Fl_Double_Window* o = new Fl_Double_Window(974, 566, "LIQR");
    w = o; if (w) {/* empty */}
    o->color(FL_DARK1);
    o->labelsize(12);
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(0, 0, 975, 20, "hfgdhf");
      o->menu(menu_hfgdhf);
    } // Fl_Menu_Bar* o
    { spectre_box = new SpectreDrawer(210, 30, 750, 115, "spectrogram");
      spectre_box->box(FL_BORDER_BOX);
      spectre_box->color((Fl_Color)24);
      spectre_box->selection_color(FL_BACKGROUND_COLOR);
      spectre_box->labeltype(FL_NORMAL_LABEL);
      spectre_box->labelfont(0);
      spectre_box->labelsize(14);
      spectre_box->labelcolor(FL_LIGHT3);
      spectre_box->align(Fl_Align(FL_ALIGN_CENTER));
      spectre_box->when(FL_WHEN_RELEASE);
      Fl_Group::current()->resizable(spectre_box);
    } // SpectreDrawer* spectre_box
    { Fl_Tree* o = new Fl_Tree(10, 30, 190, 520);
      o->color((Fl_Color)53);
    } // Fl_Tree* o
    { Fl_Counter* o = center_freq_toggle = new Fl_Counter(210, 180, 180, 20, "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\
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
    { Fl_Group* o = new Fl_Group(575, 350, 190, 200, "\320\224\320\225\320\234\320\236\320\224\320\243\320\233\320\257\320\242\320\
\236\320\240");
      o->box(FL_THIN_UP_BOX);
      o->labelsize(10);
      o->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
      { Fl_Group* o = new Fl_Group(585, 405, 170, 55, "\320\220\320\235\320\220\320\233\320\236\320\223\320\236\320\222\320\220\320\
\257 \320\224\320\225\320\234\320\236\320\224\320\243\320\233\320\257\320\246\
\320\230\320\257");
        o->box(FL_ENGRAVED_BOX);
        o->labelsize(9);
        o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
        { Fl_Round_Button* o = new Fl_Round_Button(595, 415, 45, 15, "AM");
          o->down_box(FL_ROUND_DOWN_BOX);
        } // Fl_Round_Button* o
        { Fl_Round_Button* o = new Fl_Round_Button(595, 435, 45, 15, "WFM");
          o->down_box(FL_ROUND_DOWN_BOX);
          o->value(1);
        } // Fl_Round_Button* o
        { Fl_Round_Button* o = new Fl_Round_Button(655, 415, 64, 15, "LSB");
          o->down_box(FL_ROUND_DOWN_BOX);
        } // Fl_Round_Button* o
        { Fl_Round_Button* o = new Fl_Round_Button(655, 435, 64, 15, "USB");
          o->down_box(FL_ROUND_DOWN_BOX);
        } // Fl_Round_Button* o
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(585, 480, 170, 60, "\320\246\320\230\320\244\320\240\320\236\320\222\320\220\320\257 \320\224\
\320\225\320\234\320\236\320\224\320\243\320\233\320\257\320\246\320\230\320\
\257");
        o->box(FL_ENGRAVED_BOX);
        o->labelsize(9);
        o->align(Fl_Align(FL_ALIGN_TOP_LEFT));
        { Fl_Round_Button* o = new Fl_Round_Button(595, 490, 45, 15, "BPSK");
          o->down_box(FL_ROUND_DOWN_BOX);
        } // Fl_Round_Button* o
        { Fl_Round_Button* o = new Fl_Round_Button(595, 510, 45, 15, "QAM8");
          o->down_box(FL_ROUND_DOWN_BOX);
        } // Fl_Round_Button* o
        { Fl_Round_Button* o = new Fl_Round_Button(660, 490, 64, 15, "LSB");
          o->down_box(FL_ROUND_DOWN_BOX);
        } // Fl_Round_Button* o
        { Fl_Round_Button* o = new Fl_Round_Button(660, 510, 64, 15, "USB");
          o->down_box(FL_ROUND_DOWN_BOX);
        } // Fl_Round_Button* o
        o->end();
      } // Fl_Group* o
      { Fl_Check_Button* o = new Fl_Check_Button(585, 370, 170, 15, "\320\220\320\262\321\202\320\276\320\277\320\276\320\264\320\261\320\276\321\
\200 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\276\
\320\262");
        o->down_box(FL_DOWN_BOX);
        o->labelsize(11);
      } // Fl_Check_Button* o
      o->end();
    } // Fl_Group* o
    { Fl_Tabs* o = new Fl_Tabs(210, 220, 360, 135);
      { Fl_Group* o = new Fl_Group(210, 240, 360, 115, "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \
\320\277\321\200\320\270\321\221\320\274\320\260");
        o->labelsize(13);
        { tabs_center_freq_field = new Fl_Value_Output(385, 250, 170, 20, "\320\246\320\265\320\275\321\202\321\200\320\260\320\273\321\214\320\275\320\
\260\321\217 \321\207\320\260\321\201\321\202\320\276\321\202\320\260, \320\
\272\320\223\321\206::");
          tabs_center_freq_field->labelsize(12);
          tabs_center_freq_field->textsize(12);
        } // Fl_Value_Output* tabs_center_freq_field
        { Fl_Value_Input* o = new Fl_Value_Input(385, 301, 170, 19, "\320\237\320\276\320\273\320\276\321\201\320\260 \320\277\321\200\320\276\
\320\277\321\203\321\201\320\272\320\260\320\275\320\270\321\217, \320\272\
\320\223\321\206:");
          o->labelsize(12);
          o->maximum(2000);
          o->value(2000);
          o->textsize(12);
          o->callback((Fl_Callback*)cb_);
        } // Fl_Value_Input* o
        { tabs_sample_rate_field = new Fl_Value_Input(385, 276, 170, 20, "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \320\264\320\270\
\321\201\320\272\321\200\320\265\321\202\320\270\320\267\320\260\321\206\320\
\270\320\270, \320\272\320\223\321\206:");
          tabs_sample_rate_field->labelsize(12);
          tabs_sample_rate_field->maximum(2000);
          tabs_sample_rate_field->textsize(12);
        } // Fl_Value_Input* tabs_sample_rate_field
        o->end();
      } // Fl_Group* o
      { Fl_Group* o = new Fl_Group(210, 240, 360, 115, "\320\236\320\261 SDR");
        o->labelsize(12);
        o->hide();
        { sdr_device_name_field = new Fl_Output(365, 250, 190, 20, "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \321\203\
\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\260:");
          sdr_device_name_field->labelsize(12);
          sdr_device_name_field->textsize(12);
        } // Fl_Output* sdr_device_name_field
        { tuner_name_field = new Fl_Output(365, 275, 190, 20, "\320\242\320\270\320\277 \321\202\321\216\320\275\320\265\321\200\320\260:");
          tuner_name_field->labelsize(12);
          tuner_name_field->textsize(12);
        } // Fl_Output* tuner_name_field
        { xtal_freq_field = new Fl_Value_Output(365, 300, 190, 20, "\320\247\320\260\321\201\321\202\320\276\321\202\320\260 \321\200\320\265\
\320\267\320\276\320\275\320\260\321\202\320\276\321\200\320\260:");
          xtal_freq_field->labelsize(12);
          xtal_freq_field->textsize(12);
        } // Fl_Value_Output* xtal_freq_field
        { tuner_gain_field = new Fl_Value_Output(365, 325, 190, 20, "\320\243\321\201\320\270\320\273\320\265\320\275\320\270\320\265 \321\202\
\321\216\320\275\320\265\321\200\320\260, \320\264\320\221:");
          tuner_gain_field->labelsize(12);
          tuner_gain_field->textsize(12);
        } // Fl_Value_Output* tuner_gain_field
        o->end();
      } // Fl_Group* o
      o->end();
    } // Fl_Tabs* o
    { Fl_Light_Button* o = new Fl_Light_Button(455, 155, 115, 20, "\320\227\320\220\320\237\320\230\320\241\320\254 I/Q (0 MB)");
      o->selection_color((Fl_Color)89);
      o->labelsize(10);
    } // Fl_Light_Button* o
    { Fl_Button* o = new Fl_Button(280, 155, 90, 20, "\320\237\320\243\320\241\320\232");
      o->tooltip("start");
      o->labelsize(10);
    } // Fl_Button* o
    { Fl_Button* o = new Fl_Button(370, 155, 85, 20, "\320\241\320\242\320\236\320\237");
      o->labelsize(10);
    } // Fl_Button* o
    { Fl_Group* o = new Fl_Group(575, 255, 190, 90, "\320\237\320\236\320\233\320\236\320\241\320\236\320\222\320\236\320\231 \
\320\244\320\230\320\233\320\254\320\242\320\240");
      o->box(FL_THIN_UP_BOX);
      o->labelsize(10);
      o->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
      { Fl_Value_Input* o = new Fl_Value_Input(695, 275, 60, 20, "\320\250\320\270\321\200\320\270\320\275\320\260 \320\277\320\276\320\273\
\320\276\321\201\321\213, \320\272\320\223\321\206:");
        o->labelsize(11);
        o->value(80);
        o->textsize(12);
      } // Fl_Value_Input* o
      { Fl_Value_Input* o = new Fl_Value_Input(695, 295, 60, 20, "\320\232\321\200\321\203\321\202\320\270\320\267\320\275\320\260 \321\201\
\320\277\320\260\320\264\320\260:");
        o->labelsize(11);
        o->value(0.5);
        o->textsize(12);
      } // Fl_Value_Input* o
      { Fl_Value_Input* o = new Fl_Value_Input(695, 315, 60, 20, "\320\224\320\265\321\206\320\270\320\274\320\260\321\206\320\270\321\217:");
        o->labelsize(11);
        o->value(2);
        o->textsize(12);
      } // Fl_Value_Input* o
      { Fl_Check_Button* o = new Fl_Check_Button(740, 255, 15, 15);
        o->down_box(FL_DOWN_BOX);
        o->value(1);
        o->labelsize(13);
      } // Fl_Check_Button* o
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(770, 255, 190, 140, "\320\232\320\220\320\235\320\220\320\233\320\254\320\235\320\253\320\231 \
\320\224\320\225\320\232\320\236\320\224\320\225\320\240");
      o->box(FL_THIN_UP_BOX);
      o->labelsize(9);
      o->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(770, 400, 190, 150, "\320\224\320\225\320\232\320\236\320\224\320\225\320\240 \320\230\320\241\
\320\242\320\236\320\247\320\235\320\230\320\232\320\220");
      o->box(FL_THIN_UP_BOX);
      o->labelsize(9);
      o->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
      o->end();
    } // Fl_Group* o
    { Fl_Light_Button* o = new Fl_Light_Button(210, 155, 70, 20, "\320\220\320\243\320\224\320\230\320\236");
      o->selection_color((Fl_Color)2);
      o->labelsize(10);
    } // Fl_Light_Button* o
    { center_freq_field = new Fl_Value_Input(395, 180, 120, 20);
      center_freq_field->labeltype(FL_NO_LABEL);
      center_freq_field->labelsize(11);
      center_freq_field->value(100000);
      center_freq_field->textsize(12);
      center_freq_field->callback((Fl_Callback*)cb_center_freq_field);
    } // Fl_Value_Input* center_freq_field
    { Fl_Group* o = new Fl_Group(575, 155, 190, 95, "\320\222\320\245\320\236\320\224");
      o->box(FL_THIN_UP_BOX);
      o->labelsize(9);
      o->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
      { Fl_Value_Output* o = new Fl_Value_Output(675, 176, 80, 20, "\320\247\320\260\321\201\321\202. \320\264\320\270\321\201\320\272\321\200., \
\320\272\320\223\321\206:");
        o->labelsize(11);
        o->value(2400);
        o->textsize(12);
      } // Fl_Value_Output* o
      { Fl_Value_Output* o = new Fl_Value_Output(675, 197, 80, 20, "\320\240\320\260\320\267\320\274\320\265\321\200 \320\272\320\260\320\264\
\321\200\320\260:");
        o->labelsize(11);
        o->value(2048);
        o->textsize(12);
      } // Fl_Value_Output* o
      { Fl_Output* o = new Fl_Output(675, 219, 80, 20, "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272:");
        o->labelsize(11);
        o->textsize(11);
      } // Fl_Output* o
      o->end();
    } // Fl_Group* o
    { Fl_Group* o = new Fl_Group(770, 155, 190, 95, "\320\222\320\253\320\245\320\236\320\224");
      o->box(FL_THIN_UP_BOX);
      o->labelsize(9);
      o->align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
      { Fl_Value_Output* o = new Fl_Value_Output(870, 176, 80, 20, "\320\247\320\260\321\201\321\202. \320\264\320\270\321\201\320\272\321\200., \
\320\272\320\223\321\206:");
        o->labelsize(11);
        o->value(1200);
        o->textsize(12);
      } // Fl_Value_Output* o
      { Fl_Value_Output* o = new Fl_Value_Output(870, 197, 80, 20, "\320\240\320\260\320\267\320\274\320\265\321\200 \320\272\320\260\320\264\
\321\200\320\260:");
        o->labelsize(11);
        o->value(1024);
        o->textsize(12);
      } // Fl_Value_Output* o
      { Fl_Output* o = new Fl_Output(870, 219, 80, 20, "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272:");
        o->labelsize(11);
        o->textsize(11);
      } // Fl_Output* o
      o->end();
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
