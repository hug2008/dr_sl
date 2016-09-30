/**
*   \file   formatsize.h
*   \author Dave Reid
*   \brief  Header file for formatsize() implementations.
*/
#ifndef DRSL_FORMATSIZE
#define DRSL_FORMATSIZE

#include "vformat.h"

namespace drsl
{

/**
*   \brief              Determines the required size of a buffer to store the specified formatted string.
*   \param  format [in] The format string to use for formatting the data.
*   \return             The number of T's required to store the formatted string based on the format string and the input parameters.
*
*   \remarks
*       The \c format parameter must be NULL terminated. This may change in the future.
*/
template <typename T>
inline size_t formatsize(const T *format, ...)
{
    va_list args;
    va_start(args, format);

    int ret = drsl::vformat((T *)NULL, 0, format, args);

    va_end(args);

    return ret;
}

}

#endif // DRSL_FORMATSIZE
