#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

class SpectreDrawer : public Fl_Box {
	int buffer_length;
	float *buffer;

public:
	SpectreDrawer(int x, int y, int w, int h, const char* l);
	void link_buffer(float *buffer, int len);
	void draw();
};
