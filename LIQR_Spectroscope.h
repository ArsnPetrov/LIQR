#pragma once
#include "LIQR_Layer.h"

template <typename buf_t>
class LIQR_Spectroscope : public LIQR_Layer<buf_t>
{
public:
	template<typename p_buf_t>
	LIQR_Spectroscope(LIQR_Layer<p_buf_t>* l) : LIQR_Layer<buf_t>{ l } {};
};