/**
*   \brief  relative.h
*   \author Dave Reid
*   \brief  Header file for the relative() implementation.
*/
#ifndef DRSL_PATHS_RELATIVE
#define DRSL_PATHS_RELATIVE

namespace drsl
{
namespace paths
{

/**
*   \brief                      Turns an absolute file path into a relative path.
*   \param  dest       [out]    Pointer to the buffer that will recieve the relative path.
*   \param  path       [in]     The absolute path that should be made relative.
*   \param  base       [in]     The path that the input path should be made relative to.
*   \param  pathLength [in]     The length in T's of the path string, not including the null terminator.
*   \param  baseLength [in]     The length in T's of the base string, not including the null terminator.
*   \return                     The number ot T's that must be allocated to store the converted path.
*
*   \remarks
*       If it is not possible to convert the path, the function will return 1 and the destination
*       will be set to an empty string.
*       \par
*       The function assumes that both \c path and \c base are absolute paths. No distinction is
*       made for "../" and "./" directory names. The aforementioned strings will be treated like
*       a normal directory name.
*       \par
*       The function does not check if the resulting path is a valid or existing directory or file.
*/
template <typename T>
inline size_t relative(T *dest, const T *path, const T *base, size_t pathLength = -1, size_t baseLength = -1)
{
    assert(path != NULL);
    assert(base != NULL);

    // First we need to retrieve the sub directories of each path.
    reference_string<const T> path_dirs[128];
    size_t path_count;
    _split_path(path_dirs, path_count, path, pathLength);

    reference_string<const T> base_dirs[128];
    size_t base_count;
    _split_path(base_dirs, base_count, base, baseLength);

    // We need to check the last base directory. If it is an empty string,
    // we want to decrement our number of items.
    if (base_dirs[base_count - 1].end - base_dirs[base_count - 1].start == 0)
    {
        --base_count;
    }

    
    // We need to determine how many common prefixed directories exist
    // between the path and the base. We then find how many directories
    // are left in the base list. This is then how many "../" we put
    // in from of the relative path.

    // First grab the path with the smallest amount of directories.
    size_t smallest_count = (path_count < base_count) ? path_count : base_count;

    // Now we compare each directory.
    size_t end_common = 0;
    for (end_common = 0; end_common < smallest_count; ++end_common)
    {
        if (!equal(path_dirs[end_common], base_dirs[end_common]))
        {
            break;
        }
    }

    // The variable that will store our final output size. We start this
    // as 1 to account for the null terminator.
    size_t final_size = 1;

    // Now we need to write each "to parent" directory to our destination.
    for (size_t i = end_common; i < base_count; ++i)
    {
        final_size += _write_parent_dir(dest);
    }

    // Now we need only write the remainder sub directories after the common
    // directories from the path.
    for (size_t i = end_common; i < path_count; ++i)
    {
        if (dest != NULL)
        {
            size_t copy_size = _copy_pair_to_str(dest, path_dirs[i]);
            dest += copy_size;

            final_size += copy_size;

            // We now need to divide the directories with a slash.
            if ((i != path_count - 1) && (path_dirs[i].end - path_dirs[i].start != 1))
            {
                // Now write the character and move the pointer forward.
                size_t char_size = writechar(dest, DRSL_PATH_SLASH);

                final_size += char_size;
            }
        }
        else
        {
            final_size += path_dirs[i].end - path_dirs[i].start;

            if ((i != path_count - 1) && (path_dirs[i].end - path_dirs[i].start != 1))
            {
                final_size += charwidth<T>(DRSL_PATH_SLASH);
            }
        }
    }

    // NULL terminate the destination.
    if (dest != NULL)
    {
        *dest = 0;
    }

    return final_size;
}


template <typename T>
inline void relative(slow_string<T> &dest, const T *path, const T *base)
{
    T *&temp = dest.c_str();

    temp = new T[relative((T *)NULL, path, base)];
    relative(temp, path, base);

    // NOTE: Don't delete the temp pointer. It will be deleted by the strings destructor.
}


inline string8 relative(const char *path, const char *base)
{
    string8 dest;
    relative(dest, path, base);

    return dest;
}
inline string16 relative(const char16_t *path, const char16_t *base)
{
    string16 dest;
    relative(dest, path, base);

    return dest;
}
inline string32 relative(const char32_t *path, const char32_t *base)
{
    string32 dest;
    relative(dest, path, base);

    return dest;
}
inline wstring relative(const wchar_t *path, const wchar_t *base)
{
    wstring dest;
    relative(dest, path, base);

    return dest;
}


/**
*   \brief                  Retrieves the size that a buffer must be in order to store a relative path.
*   \param  path       [in] The absolute path that is to be converted to a relative path.
*   \param  base       [in] The absolute path that the \c path parameter should be made relative to.
*   \param  pathLength [in] The length in T's of the \c path string, not including the null terminator.
*   \param  baseLength [in] The length in T's of the \c path string, not including the null terminator.
*   \return                 The number of T's required to store the relative path.
*/
template <typename T>
inline size_t relativesize(const T *path, const T *base, size_t pathLength = -1, size_t baseLength = -1)
{
    return relative((T *)NULL, path, base, pathLength, baseLength);
}

}
}

#endif // DRSL_PATHS_RELATIVE
