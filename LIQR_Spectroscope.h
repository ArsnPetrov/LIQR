#pragma once
#include "LIQR_Layer.h"

template <typename buf_t>
class LIQR_Spectroscope : public LIQR_Layer<buf_t>
{
public:
	LIQR_Spectroscope();

	void update();	
};

