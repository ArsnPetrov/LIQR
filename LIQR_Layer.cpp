#include "LIQR_Layer.h"

template<typename buf_t>
LIQR_Layer<buf_t>::LIQR_Layer()
{
	
}

template<typename buf_t>
LIQR_Layer<buf_t>::LIQR_Layer(int len)
{
	buffer = new buf_t[len];
}

template<typename buf_t>
template<typename p_buf_t>
LIQR_Layer<buf_t>::LIQR_Layer(LIQR_Layer<p_buf_t>* l)
{
		l->_add_listener(this);
}

template<typename buf_t>
template<typename p_buf_t>
inline void LIQR_Layer<buf_t>::listen_to(LIQR_Layer<p_buf_t>* l)
{
		l->_add_listener(this);
		parent = l;
}

template<typename buf_t>
void LIQR_Layer<buf_t>::call_down()
{
	for (uint32_t i = 0; i < children.size(); i++)
	{
		children[i]->update();
	}
}

template<typename buf_t>
void LIQR_Layer<buf_t>::update()
{
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
void LIQR_Layer<buf_t>::_add_listener(LIQR_Layer* l)
{
	children.push_back(l);
}

template class LIQR_Layer<cmplx_uint8_t>;
template LIQR_Layer<cmplx_uint8_t>::LIQR_Layer(int len);

template class LIQR_Layer<float>;
template LIQR_Layer<float>::LIQR_Layer(LIQR_Layer<cmplx_uint8_t>* l);