#include "LIQR_Layer.h"
#include "LIQR_Receiver.h"
#include "LIQR_Spectroscope.h"

template<typename buf_t>
LIQR_Layer<buf_t>::LIQR_Layer()
{
	type = LAYER_BASE;
}

template<typename buf_t>
LIQR_Layer<buf_t>::LIQR_Layer(int len)
{
	type = LAYER_BASE;
	buffer = new buf_t[len];
}

template<typename buf_t>
void LIQR_Layer<buf_t>::listen_to(LIQR_Layer<buf_t>* l)
{
	l->_add_listener(this);
	parent = l;
}

template<typename buf_t>
void LIQR_Layer<buf_t>::call_down()
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

template<typename buf_t>
void LIQR_Layer<buf_t>::update()
{
	call_down();
}

template<typename buf_t>
uint32_t LIQR_Layer<buf_t>::get_length()
{
	return length;
}

template<typename buf_t>
buf_t LIQR_Layer<buf_t>::get_sample(uint32_t i)
{
	return buffer[i];
}

template<typename buf_t>
void LIQR_Layer<buf_t>::_add_listener(LIQR_Layer<buf_t>* l)
{
	children.push_back(l);
}

template class LIQR_Layer<cmplx_uint8_t>;
template class LIQR_Layer<float>;