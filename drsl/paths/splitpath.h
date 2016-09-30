/**
*   \file   splitpath.h
*   \author Dave Reid
*   \brief  Header file for the splitpath() implementation.
*/
#ifndef __DRSL_PATHS_SPLITPATH_H_
#define __DRSL_PATHS_SPLITPATH_H_

namespace drsl
{
namespace paths
{

/**
*   \brief               Splits a path into two parts, where the first part contains the folder path and the second part contains the file name.
*   \param  path   [in]  The path to split.
*   \param  folder [out] The string that will recieve the folder part.
*   \param  file   [out] The string that will recieve the file part.
*/
template <typename T>
void splitpath(T *path, reference_string<T> &folder, reference_string<T> &file, size_t pathLength = -1)
{
    assert(path != NULL);

    // We first need to find the last slash in the path. Once we have that we can output
    // our results.

    // Stores the start of the next character. This is used so that we can modify pathLength easily.
    const T *start_of_ch = path;

    // The start of the folder is always at the start of the string.
    folder.start = folder.end = path;

    char32_t ch;
    while (pathLength > 0 && (ch = drsl::nextchar(path)) != '\0')
    {
        if (ch == '/' || ch == '\\')
        {
            folder.end = path;
        }

        pathLength -= path - start_of_ch;
        start_of_ch = path;
    }

    // Now we can output our results. The file starts where the folder ends.
    file.start = folder.end;
    file.end = path;
}

}
}

#endif  // __DRSL_PATHS_SPLITPATH_H_
