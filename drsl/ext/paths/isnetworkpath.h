/**
*   \brief  isnetworkpath.h
*   \author Dave Reid
*   \brief  Header file for the isnetworkpath() implementation.
*/
#ifndef __DRSL_PATHS_ISNETWORKPATH_H_
#define __DRSL_PATHS_ISNETWORKPATH_H_

#include "../../nextchar.h"

namespace drsl
{
namespace paths
{

/**
*   \brief                  Checks to see if the specified string is a network path.
*   \param  path       [in] The path to check.
*   \param  pathLength [in] The length in T's of the path, not including the null terminator.
*   \return                 True if the path is a network path; false otherwise.
*/
template <typename T>
inline bool isnetworkpath(const T *path, size_t pathLength = -1)
{
#if (PLATFORM == PLATFORM_WINDOWS)
    if (pathLength < 2)
    {
        return false;
    }

    // We need to look at the first character. If it is a slash, we need to look at the next one.
    char32_t ch = nextchar(path);
    if (ch == '\\' || ch == '/')
    {
        // Grab the next character. If it is also a back slash, we have a network path.
        ch = nextchar(path);
        if (ch == '\\' || ch == '/')
        {
            return true;
        }
    }
#else
#pragma message ("Warning: isnetworkpath() is only supported on Windows for the moment.")
#endif

    return false;
}

}
}

#endif // __DRSL_PATHS_ISNETWORKPATH_H_
