#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <pthread.h>
#include <stdint.h>
#include "util.h"

class SpectreDrawer : public Fl_Box {
	int buffer_length;
	float *buffer;
	uint32_t bandwidth;
	uint32_t frequency;
	pthread_t thread;

public:
	bool no_fftshift;

	SpectreDrawer(int x, int y, int w, int h, const char* l);
	void link_buffer(float *buffer, int len);
	void change_buffer(float* buf, int len);
	void set_bandwidth(uint32_t freq);
	void set_frequecny(uint32_t freq);
	void draw();
	void _redraw();
};
