#include "SpectreDrawer.h"
#include <cfloat>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void spectre_drawer_callback(void *arg)
{
	((SpectreDrawer*)arg)->redraw();
	Fl::repeat_timeout(0.01, spectre_drawer_callback, arg);
}

SpectreDrawer::SpectreDrawer(int x, int y, int w, int h, const char* l) : Fl_Box(x, y, w, h, l), thread()
{
	buffer_length = 0;
	buffer = NULL;
}

void SpectreDrawer::link_buffer(float* buf, int len)
{
	buffer_length = len;
	buffer = buf;

	Fl::add_timeout(0.1, spectre_drawer_callback, this);
}

void SpectreDrawer::draw()
{
	float max = FLT_MIN, min = FLT_MAX, range, step;
	int x0 = x(), y0 = y(), window_width = w(), window_height = h();

	//printf("Buffer size is %d\n", buffer_length);

	fl_color(92, 92, 104);
	fl_draw_box(FL_DOWN_BOX, x0, y0, window_width, window_height, fl_color());

	if (buffer)
	{
		for (int i = 0; i < buffer_length; i++)
		{
			if (buffer[i] > max) max = buffer[i];

			if (buffer[i] < min) min = buffer[i];
		}

		range = max - min;
		step = range / window_height;

		fl_color(148, 148, 160);
		fl_begin_line();
		for (int i = 0; i < buffer_length; i++)
		{
			int _x = x0 + i * ((float)window_width / buffer_length);
			int _y = y0 + 300 + window_height / 2 - buffer[(i + buffer_length / 2) % buffer_length] * 4;

			if (_y < y0) _y = y0;
			if (_y > y0 + window_height) _y = y0 + window_height - 2;
			if (_x < x0) _x = x0;
			if (_x > _x + window_width) _x = x0 + window_width - 2;

			fl_vertex(_x, _y);
			fl_vertex(_x, y0 + window_height);
			
			
			//printf("hello world [%d] = %f\n", i, buffer[i]);
		}
		fl_end_line();
		
	}
}
