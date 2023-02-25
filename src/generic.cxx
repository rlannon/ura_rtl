#include "generic.hxx"

URA_RTL_BEGIN

Generic Generic::copy() const
{
    Generic g;
    g._value = _value;
    
    return g;
}

URA_RTL_END
