#pragma once

#include "rtl.hxx"

URA_RTL_BEGIN

class Generic
{
    double _value;  // NaN-boxed generic

public:
    Generic copy() const;   // Creates a copy; adds reference to owned object if applicable
};

URA_RTL_END
