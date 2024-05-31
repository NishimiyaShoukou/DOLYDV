#pragma once
#include <stdint.h>


namespace Timer
{
    int64_t   reset(void);


    int64_t   elapsed_us(void);

    int64_t   elapsed_ms(void);

    int64_t   elapsed(void);
};
