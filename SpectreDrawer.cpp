#include "SpectreDrawer.h"
#include <cfloat>
#include <string>
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
	bandwidth = MHz(2);
	frequency = MHz(100);
}

void SpectreDrawer::link_buffer(float* buf, int len)
{
	buffer_length = len;
	buffer = buf;

	Fl::add_timeout(0.01, spectre_drawer_callback, this);
}

void SpectreDrawer::draw()
{
	float max = FLT_MIN, min = FLT_MAX, range, step;
	int x0 = x(), y0 = y(), window_width = w(), window_height = h();

	//printf("Buffer size is %d\n", buffer_length);

	fl_color(92, 92, 104);
	fl_draw_box(FL_DOWN_BOX, x0, y0, window_width, window_height, fl_color());

	fl_push_clip(x0 + 2, y0 + 2, window_width, window_height - 4);

	if (buffer)
	{
		// frequencies

		uint32_t number_of_lines = bandwidth / kHz(100);

		double pixels_per_100kHz = (double)window_width / number_of_lines;
		double offset = (bandwidth % kHz(100)) * pixels_per_100kHz / 100;

		for (uint32_t i = 0; i < number_of_lines; i++)
		{
			if (i == number_of_lines / 2)
			{
				fl_color(FL_BLACK);
			}
			else
			{
				fl_color(74, 74, 85);
			}
			fl_begin_line();
			fl_vertex(x0 + offset + i * pixels_per_100kHz, y0 + 17);
			fl_vertex(x0 + offset + i * pixels_per_100kHz, y0 - 3 + window_height);
			//printf("x = %d y = %d \n", offset + i * pixels_per_100kHz, y0);
			fl_end_line();

			
			if (i == number_of_lines / 2)
			{
				fl_color(FL_WHITE);
			}
			else
			{
				fl_color(148, 148, 160);
			}
			fl_font(0, 10);

			std::string freq_str = std::to_string((frequency - bandwidth / 2 + bandwidth % kHz(100) + i * kHz(100)) / 1000000);
			freq_str += '.';
			freq_str += std::to_string((frequency - bandwidth / 2 + bandwidth % kHz(100) + i * kHz(100)) / 100000 % 10);
			fl_draw(freq_str.c_str(), x0 + offset + i * pixels_per_100kHz - 25, y0 + 5, 50, 10, FL_ALIGN_CENTER, NULL, 1);
		}

		// dB

		int _y = y0;
		for (int i = 2; i < 12; i += 2)
		{
			fl_color(74, 74, 85);
			fl_begin_line();
			fl_vertex(x0 + 3, _y + 10 * i);
			fl_vertex(x0 + window_width - 3, _y + 10 * i);
			fl_end_line();

			fl_color(148, 148, 160);
			std::string dbstr = "-" + std::to_string(i * 10) + " dBFS";
			fl_draw(dbstr.c_str(), x0 + 3, _y + 10 * i - 5, 50, 9, FL_ALIGN_CENTER, NULL, 1);
		}

		// spectre

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
			int _y = y0 - buffer[(i + buffer_length / 2) % buffer_length];

			if (_y < y0) _y = y0;
			if (_y > y0 + window_height - 4) _y = y0 + window_height - 4;
			if (_x < x0 + 60) _x = x0 + 60;
			if (_x > x0 + window_width - 4) _x = x0 + window_width - 4;

			fl_vertex(_x, _y);
			fl_vertex(_x, y0 + window_height - 4);
			
			
			//printf("hello world [%d] = %f\n", i, buffer[i]);
		}
		fl_end_line();
	}

	fl_pop_clip();
}
