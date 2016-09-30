// Copyright (C) 2016 David Reid. See included LICENSE file.

#ifndef DRSL_GETCHAR
#define DRSL_GETCHAR

namespace drsl
{

/**
*   \brief                 Retrieves a character from the specified string.
*   \param  str       [in] The string to retrieve the character from.
*   \param  index     [in] The zero based index of the character to retrieve.
*   \param  strLength [in] The length in T's of the string, not including the null terminator.
*   \return                The character at the location specified by the index.
*
*   \remarks
*       If the index is not valid, results are undefined.
*/
#ifdef DRSL_ONLY_ASCII
template <typename T>
inline char32_t getchar(const T *str, size_t index, size_t strLength = -1)
{
    if (strLength != -1)
    {
        if (index >= strLength)
        {
            return NULL;
        }
    }

    return (char32_t)str[index];
}
template <> inline char32_t getchar(const char *str, size_t index, size_t strLength)
{
    if (strLength != -1)
    {
        if (index >= strLength)
        {
            return NULL;
        }
    }

    return (char32_t)(unsigned char)str[index];
}
template <> inline char32_t getchar(const char16_t *str, size_t index, size_t strLength)
{
    if (strLength != -1)
    {
        if (index >= strLength)
        {
            return NULL;
        }
    }

    return (char32_t)(char16_t)str[index];
}
#else
template <typename T>
inline char32_t getchar(const T *str, size_t index, size_t strLength = -1)
{
    const T *temp = str;

    // Stores the start of the next character.
    const T *start_of_ch = str;

    char32_t ch;
    while (strLength > 0 && (ch = drsl::nextchar(temp)) != '\0')
    {
        size_t cur_pos = temp - str;

        strLength -= temp - start_of_ch;
        start_of_ch = temp;

        if (cur_pos == index + 1)
        {
            return ch;
        }
        else if (cur_pos > index + 1)
        {
            return 0;
        }
    }

    return 0;
}

// Optimized case.
inline char32_t getchar(const char32_t *str, size_t index, size_t strLength = -1)
{
    if (strLength != (size_t)-1)
    {
        if (index >= strLength)
        {
            return '\0';
        }
    }

    return static_cast<char32_t>(str[index]);
}
#endif

inline char32_t getchar(const wchar_t *str, size_t index, size_t strLength = -1)
{
    switch (sizeof(wchar_t))
    {
    case 2: return getchar((const char16_t *)str, index, strLength);
    case 4: return getchar((const char32_t *)str, index, strLength);
    }

    return getchar((const char *)str, index, strLength);
}


template <typename T>
inline char32_t getchar(const reference_string<T> &str, size_t index)
{
    return getchar(str.start, index, str.end - str.start);
}


}

#endif // DRSL_GETCHAR
