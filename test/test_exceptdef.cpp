#include <iostream>
#include "../src/exceptdef.hpp"


int main()
{
    WZY_DEBUG(false);

    WZY_THROW_LENGTH_ERROR_IF(true, "length error");

    WZY_THROW_OUT_OF_RANGE_IF(true, "out of range");

    WZY_THROW_RUNTIME_ERROR_IF(true, "runtime error");

    return 0;
}