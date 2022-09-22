#include "LIQR_Spectroscope.h"

template<typename buf_t>
LIQR_Spectroscope<buf_t>::LIQR_Spectroscope()
{
    type = LAYER_SPECTROSCOPE;
}

template<typename buf_t>
void LIQR_Spectroscope<buf_t>::update()
{
    if (rand() % 100 == 34) printf("i am spectroscope\n");
}

template class LIQR_Spectroscope<cmplx_uint8_t>;