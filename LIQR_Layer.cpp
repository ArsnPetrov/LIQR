#include "LIQR_Layer.h"
#include "LIQR_Receiver.h"
#include "LIQR_Spectroscope.h"

LIQR_Layer::LIQR_Layer() :
	thread(), type(LAYER_BASE), buffer(nullptr), parent(nullptr),
	length(0), sample_rate(kHz(2048)), abs_value_buffer(nullptr)
{
	abs_value_buffer = new float[length];
}

LIQR_Layer::LIQR_Layer(int len) :
	thread(), type(LAYER_BASE), parent(nullptr),
	length(len), sample_rate(kHz(2048)), abs_value_buffer(nullptr)
{
	buffer = new cmplx_float_t[len * 2];
	abs_value_buffer = new float[length];
}

void LIQR_Layer::listen_to(LIQR_Layer* l)
{
	l->_add_listener(this);
	parent = l;
}

void LIQR_Layer::call_down()
{
	for (uint32_t i = 0; i < children.size(); i++)
	{
		switch (children[i]->type)
		{
		case LAYER_BASE: children[i]->update(); break;
		case LAYER_RECEIVER: ((LIQR_Receiver*)children[i])->update(); break;
		case LAYER_SPECTROSCOPE: ((LIQR_Spectroscope*)children[i])->update(); break;
		default: printf("Error: Layer not enumerated\n"); break;
		}
		
	}
}

void LIQR_Layer::update()
{
	call_down();
}

void LIQR_Layer::calculate_abs_buffer()
{
	for (uint32_t i = 0; i < length; i++)
	{
		abs_value_buffer[i] = buffer[i].real;
	}
}

uint32_t LIQR_Layer::get_length()
{
	return length;
}

cmplx_float_t LIQR_Layer::get_sample(uint32_t i)
{
	return buffer[i];
}

fftwf_complex* LIQR_Layer::get_fftwf_buffer()
{
	return (fftwf_complex*)buffer;
}

cmplx_float_t* LIQR_Layer::get_cmplx_buffer()
{
	return buffer;
}

float* LIQR_Layer::get_abs_buffer()
{
	return abs_value_buffer;
}

void LIQR_Layer::_add_listener(LIQR_Layer* l)
{
	children.push_back(l);
}
