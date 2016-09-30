/**
*   \file   charcount.h
*   \author Dave Reid
*   \brief  Header file for chrcount() implementations.
*/
#ifndef DRSL_CHARCOUNT
#define DRSL_CHARCOUNT

namespace drsl
{

/**
*   \brief                 Retrieves the number of characters in the given string.
*   \param  str       [in] The string to check.
*   \param  strLength [in] The length in T's of the string, not including the null terminator.
*   \return                The number of characters that make up the string; or 0 if an error occurs.
*
*   \remarks
*       The input string must be null terminated. The null terminator should be the same size
*       as that of the strings internal character.
*       \par
*       This function does not return the number of bytes in the string. Rather, it calculates
*       the number of characters in the string, not including the null terminator.
*/
template <typename T>
inline size_t charcount(const T *str, size_t strLength)
{
    const T *temp = str;
    size_t count = 0;
    while (static_cast<size_t>(temp - str) < strLength && drsl::nextchar(temp) != '\0')
    {
        ++count;
    }

    return count;
}

// Optimized case. Uses drsl::length() if we're only using ASCII.
template <typename T>
inline size_t charcount(const T *str)
{
#ifdef DRSL_ONLY_ASCII
    return drsl::length(str);
#endif

    return charcount(str, (size_t)-1);
}

template <typename T>
inline size_t charcount(const reference_string<T> &str)
{
    return charcount(str.start, str.end - str.start);
}

}

#endif // DRSL_CHARCOUNT
