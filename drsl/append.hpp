/**
*   \file   append.h
*   \author Dave Reid
*   \brief  Header file for append() implementations.
*/
#ifndef DRSL_APPEND
#define DRSL_APPEND

namespace drsl
{

/**
*   \brief                     Appends a string onto another string.
*   \param  dest         [out] The string that will be appended with the other string.
*   \param  source       [in]  The string to append to the destination string.
*   \param  destSize     [in]  The size in T's of the buffer pointed to by \c dest.
*   \param  destLength   [in]  The number of T's making up the existing string in \c dest, not including the null terminator.
*   \param  sourceLength [in]  The number of T's making up the source string, not including the null terminator.
*   \return                    The number of T's at a minimum that are required to store the full catenated string plus the null terminator.
*
*   \remarks
*       The destination buffer must be NULL terminated to indicate the end of the string.
*       \par
*       If an error occurs, 0 is returned.
*/
template <typename T>
size_t append(T *dest, const T *source, size_t destSize = -1, size_t destLength = -1, size_t sourceLength = -1)
{
    if (source == NULL || destSize == 0)
    {
        return 0;
    }

    // Our temporary size so that we can calculate the number of T's we need for the return value.
    size_t append_size = 0;

    // We need to get to the end of the destination string.
    while (destSize > 1 && destLength > 0 && *dest != '\0')
    {
        ++dest;
        ++append_size;
        --destSize;
        --destLength;
    };

    // Now simply copy the string over.
    if (dest != NULL)
    {
        append_size += drsl::copy(dest, source, destSize, sourceLength);
    }
    else
    {
        append_size += drsl::copysize<T>(source, sourceLength);
    }

    return append_size;
}

/**
*   \brief                     Appends a string onto another string.
*   \param  dest         [out] The string that will be appended with the other string.
*   \param  source       [in]  The string to append to the destination string.
*   \param  destSize     [in]  The size in T's of the buffer pointed to by \c dest.
*   \param  destLength   [in]  The number of T's making up the existing string in \c dest, not including the null terminator.
*   \return                    The number of T's at a minimum that are required to store the full catenated string plus the null terminator.
*
*   \remarks
*       The destination buffer must be NULL terminated to indicate the end of the string.
*       \par
*       If an error occurs, 0 is returned.
*/
template <typename T>
inline size_t append(T *dest, const reference_string<T> &source, size_t destSize = -1, size_t destLength = -1)
{
    return append(dest, source.start, destSize, destLength, length(source));
}


/**
*   \brief                  Determines the size required for a buffer to store the specified string.
*   \param  str1       [in] The first string to consider for the concatination.
*   \param  str2       [in] The second string to consider for the concatination.
*   \param  str1Length [in] The length in T's of the first string, not including the null terminator.
*   \param  str2Length [in] The length in T's of the first string, not including the null terminator.
*   \return                 The minimum size that a buffer must be in order to store the concatination of the two strings.
*
*   \remarks
*       If is safe for \c str1Length and/or \c str2Length to be set to -1, in which case the
*       function will assume that the appropriate string is null terminated.
*/
template <typename T>
inline size_t appendsize(const T *str1, const T *str2, size_t str1Length = -1, size_t str2Length = -1)
{
    return append((T *)str1, str2, (size_t)-1, str1Length, str2Length);
}
}

#endif // DRSL_APPEND
