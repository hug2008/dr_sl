/**
*   \file   _private.h
*   \author Dave Reid
*   \brief  Header file for non-public functions for the paths extension.
*/
#ifndef DRSL_PATHS_PRIVATE
#define DRSL_PATHS_PRIVATE

// Defines the directory slash for platforms.
#if (PLATFORM == PLATFORM_WINDOWS)
#define DRSL_PATH_SLASH     '\\'
#else
#define DRSL_PATH_SLASH     '/'
#endif

namespace drsl
{
namespace paths
{

template <typename T>
inline void _split_path(reference_string<const T> (&dest)[128], size_t &count, const T *path, size_t pathLength)
{
    // Our current sub directory. There is always at least one sub directory.
    reference_string<const T> current_pair;
    current_pair.start = path;

    // We need to ensure that our counter is at 0.
    count = 0;

    const T *temp = path;
    char32_t ch;
    while (pathLength > 0 && (ch = drsl::nextchar(temp)) != '\0')
    {
        if (ch == '\\' || ch == '/')
        {
            current_pair.end = path;

            if (current_pair.end - current_pair.start != 0)
            {
                dest[count++] = current_pair;

                // We need to return straight away if we have too many sub directories.
                if (count == 128)
                {
                    return;
                }
            }

            // Now we can start our new string.
            current_pair.start = temp;
        }

        pathLength -= temp - path;
        path = temp;
    }

    // We need to add our last string to the list.
    current_pair.end = temp;
    dest[count++] = current_pair;
}

/**
*   \brief              Determines if the specified string pair is equal to ".."
*   \param  dir [in]    The directory pair to check.
*   \return             True if the string is equal to ".."
*/
template <typename T>
inline bool _pair_is_parent_dir(const reference_string<const T> &dir)
{
    const T *temp = dir.start;
    char32_t ch1 = drsl::nextchar(temp);
    char32_t ch2 = drsl::nextchar(temp);
    if (temp == dir.end && ch1 == '.' && ch2 == '.')
    {
        return true;
    }

    return false;
}

/**
*   \brief              Copies a directory pair to a string.
*   \param  dest [out]  Pointer to the buffer that the string pair will be copied to.
*   \param  pair [in]   The pair that will be copied to the destination buffer.
*   \return             The number of T's that are copied over.
*/
template <typename T>
inline size_t _copy_pair_to_str(T *dest, const reference_string<const T> &pair)
{
    // Stores the number of T's that we're copying over.
    size_t count = 0;

    if (pair.start != pair.end)
    {
        const T *temp = pair.start;
        while (temp != pair.end)
        {
            // Grab the next character.
            char32_t ch = drsl::nextchar(temp);

            // Now write the character.
            size_t char_size = writechar(dest, ch);

            count += char_size;
        }
    }

    return count;
}

/**
*   \brief              Writes the "../" directory to the destination.
*   \param  dest [out]  The string that will recieve the "../" string.
*   \return             The number of T's that are written to the destination.
*
*   \remarks
*       If \c dest is NULL, the function will return the number of T's that are required
*       to store the "../" string.
*       \par
*       On Windows platforms, the string is "..\".
*       \par
*       This function will move the destination pointer forward to just past the newly
*       written string.
*/
template <typename T>
inline size_t _write_parent_dir(T *&dest)
{
    size_t count = 0;

    size_t char_size = charwidth<T>('.');
    if (dest != NULL)
    {
        writechar(dest, '.');
        writechar(dest, '.');
    }
    count += char_size * 2;

    char_size = charwidth<T>(DRSL_PATH_SLASH);
    if (dest != NULL)
    {
        writechar(dest, DRSL_PATH_SLASH);
    }
    count += char_size;

    return count;
}


}
}

#endif // DRSL_PATHS_PRIVATE
