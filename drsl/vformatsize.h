/**
*   \file   vformatsize.h
*   \author Dave Reid
*   \brief  Header file for vformatsize() implementations.
*/
#ifndef __DRSL_VFORMATSIZE_H_
#define __DRSL_VFORMATSIZE_H_

#include "vformat.h"

namespace drsl
{

/**
*   \brief              Determines the required size of a buffer to store the specified formatted string.
*   \param  format [in] The format string to use for formatting the data.
*   \return             The number of T's required to store the formatted string based on the format string and the input parameters.
*/
template <typename T>
inline size_t vformatsize(const T *format, ...)
{
    va_list args;
    va_start(args, format);

    int ret = drsl::vformat((T *)NULL, 0, format, args);

    va_end(args);

    return ret;
}

}

#endif // __DRSL_VFORMATSIZE_H_
