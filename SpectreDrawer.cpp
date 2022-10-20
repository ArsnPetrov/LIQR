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

SpectreDrawer::SpectreDrawer(int x, int y, int w, int h, const char* l) : 
	Fl_Box(x, y, w, h, l), no_fftshift(false), thread()
{
	buffer_length = 0;
	buffer = NULL;
	bandwidth = MHz(2);
	frequency = MHz(100);
}

void SpectreDrawer::change_buffer(float* buf, int len)
{
	buffer_length = len;
	buffer = buf;
}

void SpectreDrawer::link_buffer(float* buf, int len)
{
	buffer_length = len;
	buffer = buf;

	Fl::add_timeout(0.01, spectre_drawer_callback, this);
}

void SpectreDrawer::set_bandwidth(uint32_t freq)
{
	bandwidth = freq;
}

void SpectreDrawer::set_frequecny(uint32_t freq)
{
	frequency = freq;
}

void SpectreDrawer::draw()
{
	float max = FLT_MIN, min = FLT_MAX, range, step;
	int x0 = x(), y0 = y(), window_width = w(), window_height = h();

	//printf("Buffer size is %d\n", buffer_length);

	fl_color(FL_BLACK);
	fl_draw_box(FL_DOWN_BOX, x0, y0, window_width, window_height, fl_color());

	fl_push_clip(x0 + 2, y0 + 2, window_width, window_height - 4);

	float downsample_factor = (float)buffer_length / window_width;

	if (buffer)
	{
		// frequencies

		uint32_t number_of_lines = 12;

		uint32_t freq_step = bandwidth / (number_of_lines);


		double pixels_per_step = (double)window_width / number_of_lines;
		double offset = (bandwidth % freq_step) * pixels_per_step / 100;

		for (uint32_t i = 0; i < number_of_lines; i++)
		{
			if (i == number_of_lines / 2)
			{
				fl_color(FL_WHITE);
			}
			else
			{
				fl_color(74, 74, 85);
			}
			fl_begin_line();
			fl_vertex(x0 + offset + i * pixels_per_step, y0 + 17);
			fl_vertex(x0 + offset + i * pixels_per_step, y0 - 3 + window_height);
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

			uint32_t MHz_freq = (frequency - bandwidth / 2 + bandwidth % freq_step + i * freq_step) / 1000000;

			std::string freq_str = std::to_string(MHz_freq);
			freq_str += '.';
			freq_str += std::to_string((frequency - bandwidth / 2 + bandwidth % freq_step + i * freq_step) / 10000 % 100);
			fl_draw(freq_str.c_str(), x0 + offset + i * pixels_per_step - 25, y0 + 5, 50, 10, FL_ALIGN_CENTER, NULL, 1);
		}

		// dB

		float scale = 3;

		int _y = y0;
		for (int i = 1; i < 13; i += 1)
		{
			fl_color(74, 74, 85);
			fl_begin_line();
			fl_vertex(x0 + 3, _y + scale * 10 * i);
			fl_vertex(x0 + window_width - 3, _y + scale * 10 * i);
			fl_end_line();

			fl_color(148, 148, 160);
			std::string dbstr = "-" + std::to_string(i * 10) + " dBFS";
			fl_draw(dbstr.c_str(), x0 + 3, _y + scale * 10 * i - 5, 50, 9, FL_ALIGN_CENTER, NULL, 1);
		}

		// spectre

		for (int i = 0; i < buffer_length; i++)
		{
			if (buffer[i] > max) max = buffer[i];

			if (buffer[i] < min) min = buffer[i];
		}

		range = max - min;
		step = range / window_height;

		//fl_color(148, 148, 160);
		//fl_begin_line();
		//for (int i = 0; i < window_width; i++)
		//{
		//	int _x = x0 + i;
		//	int _y = y0 - 30 - 1.5 * buffer[(int)(i * downsample_factor + buffer_length / 2) % buffer_length];

		//	if (_y < y0) _y = y0;
		//	if (_y > y0 + window_height - 4) _y = y0 + window_height - 4;
		//	if (_x < x0 + 60) _x = x0 + 60;
		//	if (_x > x0 + window_width - 4) _x = x0 + window_width - 4;

		//	fl_vertex(_x, _y);
		//	fl_vertex(_x, y0 + window_height - 4);
		//	
		//	
		//	//printf("hello world [%d] = %f\n", i, buffer[i]);
		//}

		//fl_end_line();

		fl_color(FL_GREEN);
		fl_begin_line();
		for (int i = 0; i < window_width; i++)
		{
			int _x = x0 + i;
			int index = no_fftshift ? (int)(i * downsample_factor + buffer_length / 2) % buffer_length : (i * downsample_factor);
			int _y = y0 - scale * buffer[index];
			/*for (int j = 0; j < (int)downsample_factor; j++)
			{
				_y -= scale * buffer[index + j] / (int)downsample_factor;
			}*/

			if (_y < y0) _y = y0;
			if (_y > y0 + window_height - 4) _y = y0 + window_height - 4;
			if (_x < x0 + 4) _x = x0 + 4;
			if (_x > x0 + window_width - 4) _x = x0 + window_width - 4;

			fl_vertex(_x, _y);


			//printf("hello world [%d] = %f\n", i, buffer[i]);
		}
		fl_end_line();
	}

	fl_pop_clip();
}
