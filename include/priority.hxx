#include "rtl.hxx"

#include <cinttypes>

URA_RTL_BEGIN

namespace priority
{
    inline const uint8_t URGENT = 0;
    inline const uint8_t HIGHEST = 1;
    inline const uint8_t MEDIUM = 128;
    inline const uint8_t LOWEST = 255;
}

URA_RTL_END
