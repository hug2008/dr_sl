// Copyright (C) 2016 David Reid. See included LICENSE file.

#ifndef DRSL_PATHS_ISABSOLUTE
#define DRSL_PATHS_ISABSOLUTE

namespace drsl
{
namespace paths
{

/**
*   \brief                  Determines if a given path is absolute.
*   \param  path       [in] The path to check for absoluteness.
*   \param  pathLength [in] The length in T's of the path, not including the null terminator.
*   \return                 True if the path is absolute; false otherwise.
*
*   \remarks
*       This function is platform independant. On Windows, an absolute path is
*       specified as "<Drive Letter>:<Path>". On Unix-like systems (pretty much
*       everything else), an absolute path is specified as "/<Path>".
*
*       This function will also check for a network drive path.
*/
template <typename T>
inline bool isabsolute(const T *path, size_t pathLength = -1)
{
    if (pathLength == 0)
    {
        return false;
    }

    // Create our temporary pointer. We need to do this so we can use the original
    // path to check if it is a network path later on.
    const T *temp = path;

    // We always need at least the first character.
    char32_t ch1 = nextchar(temp);

#if (PLATFORM == PLATFORM_WINDOWS)
    if (static_cast<size_t>(temp - path) <= pathLength)
    {
        // If the first character is a letter, we need to check if the second character
        // is a colon. If it is, the path is absolute.
        if ((ch1 >= 'A' && ch1 <= 'Z') || (ch1 >= 'a' && ch1 <= 'z'))
        {
            char32_t ch2 = nextchar(temp);
            if (ch2 == ':')
            {
                return true;
            }
        }
    }
#else
    // We need only check the first character. If it is a forward slash, it's
    // considered absolute.
    if (ch1 == '/')
    {
        return true;
    }
#endif

    // If we've made it here, we need to check if the path is a network path.
    return isnetworkpath(path, pathLength);
}

}
}

#endif // DRSL_PATHS_ISABSOLUTE
