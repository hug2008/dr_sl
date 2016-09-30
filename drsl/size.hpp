// Copyright (C) 2016 David Reid. See included LICENSE file.

namespace drsl
{
/**
*   \brief           Retrieves the length of a C style string.
*   \param  str [in] The string to retrieve the length of.
*   \return          The length of the C style string.
*
*   \remarks
*       This function return the number of basic character units in the string. A
*       "basic character unit" is a 'char' for char* strings and a 'wchar_t' in
*       whcar_t* strings. The same sort of things applies for UTF strings.
*       \par
*       To retrieve the number of characters in the string insteaad of basic character
*       units, use charcount() instead.
*/
template <typename T>
inline size_t length(const T *str)
{
    assert(str != NULL);

    const T *temp = str;

    while (*temp != '\0')
    {
        ++temp;
    }

    return temp - str;
}

// Optimized cases.
inline size_t length(const char *str)
{
    assert(str != NULL);

    return ::strlen(str);
}
inline size_t length(const wchar_t *str)
{
    assert(str != NULL);

    return ::wcslen(str);
}

template <typename T>
inline size_t length(const reference_string<T> &str)
{
    assert(str.end >= str.start);

    return str.end - str.start;
}





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