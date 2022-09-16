#include "SpectreDrawer.h"
#include <cfloat>

SpectreDrawer::SpectreDrawer(int x, int y, int w, int h, const char* l) : Fl_Box(x, y, w, h, l)
{
	buffer_length = 0;
	buffer = NULL;
}

void SpectreDrawer::link_buffer(float* buf, int len)
{
	buffer_length = len;
	buffer = buf;
}

void SpectreDrawer::draw()
{
	float max = FLT_MIN, min = FLT_MAX, range, step;
	int x0 = x(), y0 = y(), window_width = w(), window_height = h();

	if (buffer)
	{
		for (int i = 0; i < buffer_length; i++)
		{
			if (buffer[i] > max) max = buffer[i];

			if (buffer[i] < min) min = buffer[i];
		}

		range = max - min;
		step = range / window_height;

		fl_color(FL_CYAN);
		fl_begin_line();
		for (int i = 0; i < buffer_length; i++)
		{
			fl_vertex(x0 + i * 10, y0 + window_height / 2 - buffer[i]);
		}
		
		fl_end_line();
	}
}
