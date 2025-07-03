#ifndef WZY_STL_EXCEPTDEF_HPP
#define WZY_STL_EXCEPTDEF_HPP

#include <stdexcept>
#include <cassert>


namespace wzy_stl
{

#define WZY_DEBUG(expr) \
    do{ \
        assert(expr); \
    } while(false)

#define WZY_THROW_LENGTH_ERROR_IF(expr, what) \
    do{ \
        if(expr) \
        { \
            throw std::length_error(what); \
        } \
    } while(false)

#define WZY_THROW_OUT_OF_RANGE_IF(expr, what) \
    do{ \
        if(expr) \
        { \
            throw std::out_of_range(what); \
        } \
    } while(false)


#define WZY_THROW_RUNTIME_ERROR_IF(expr, what) \
    do{ \
        if(expr) \
        { \
            throw std::runtime_error(what); \
        } \
    } while(false)

}

#endif