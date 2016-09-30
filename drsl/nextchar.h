/**
*   \file   nextchar.h
*   \author Dave Reid
*   \brief  Header file for the nextchar() family of functions.
*/
#ifndef DRSL_NEXTCHAR
#define DRSL_NEXTCHAR

#include <assert.h>
#include "_private.h"
#include "reference_string.h"

#ifndef NULL
#define NULL 0
#endif

namespace drsl
{

/**
*   \brief                Retrieves the next character in a UTF-8 string.
*   \param  str [in, out] The string whose next character should be retrieved.
*   \return               The character that was being pointed to by \c str.
*
*   \remarks
*       If this function returns NULL, the null terminator was retrieved. When this occurs, the string
*       is _not_ moved forward to the next character (there is no characters after the null terminator).
*/
inline char32_t nextchar_utf8(const char *&str)
{
    assert(str != NULL);

#ifdef DRSL_ONLY_ASCII
    char32_t ch = *str;

    if (ch != '\0')
    {
        ++str;
    }

    return ch;
#else
    const char *source = str;

    // The character we will eventually be returning.
    char32_t ch = 0;

    // We need to determine the additional bytes that we need to read in order
    // to reconstruct the final character. We can calculate the total number of
    // bytes used for the character by adding 1 to the returned value.
    unsigned short extra_bytes = g_trailingBytesForUTF8[(unsigned char)*source];

    // We need to make sure that the null terminator is not encounted one once
    // of these bytes. If it is, we need to return 0.
    for (unsigned short i = 1; i <= extra_bytes; ++i)
    {
        if (*(source + i) == '\0')
        {
            return 0;
        }
    }

    // We need to make sure we have a valid UTF-8 character. If it isn't, we will
    // return NULL.
    if (!is_legal_utf8(source, extra_bytes + 1))
    {
        return 0;
    }

    // It is possible that the additional bytes are values of 5 and 4. This used
    // to be valid, but is not anymore. We will use the swith fall-through method
    // used in the sample code by Unicode, Inc.
    switch (extra_bytes)
    {
    case 5: ch += (unsigned char)*source++; ch <<= 6;
    case 4: ch += (unsigned char)*source++; ch <<= 6;
    case 3: ch += (unsigned char)*source++; ch <<= 6;
    case 2: ch += (unsigned char)*source++; ch <<= 6;
    case 1: ch += (unsigned char)*source++; ch <<= 6;
    case 0: ch += (unsigned char)*source++;
    }

    // Now we need to subtract a value from the character depending on the number
    // of extra bytes.
    ch -= g_offsetsFromUTF8[extra_bytes];

    // If the character is a null terminator, we don't want to modify the string.
    if (ch != '\0')
    {
        str = source;
    }

    return ch;
#endif
}

inline char32_t nextchar_utf16(const char16_t *&str)
{
    assert(str != NULL);

#ifdef DRSL_ONLY_ASCII
    char32_t ch = *str;

    if (ch != '\0')
    {
        ++str;
    }

    return ch;
#else
    const char16_t *source = str;

    // The character that we'll eventually be returning.
    char32_t ch = (char32_t)(char16_t)*source++;

    // We need to check if we have a surrogate pair. If we do, we need to do a conversion.
    // We only want to do this if the character we just retrieved wasn't a null terminator,
    // otherwise 'source' is already pointing to an invalid memory address.
    if (ch != 0)
    {
        if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_START)
        {
            // Make sure the source isn't at it's null terminator. If it is, we have an
            // error, so we will return 0.
            if (*source != 0)
            {
                // Grab our next 16-bits. This must be the low surrogate. If it isn't, we
                // have an error and need to return 0.
                char32_t ch2 = (char32_t)(char16_t)*source;

                if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END)
                {
                    ch = ((ch - UNI_SUR_HIGH_START) << UNI_HALF_SHIFT) + (ch2 - UNI_SUR_LOW_START) + UNI_HALF_BASE;
                    ++source;
                }
                else
                {
                    // The next 16-bits isn't a low surrogate, so we have an error.
                    return 0;
                }
            }
            else
            {
                // We've prematurely reached the null terminator, so return 0.
                return 0;
            }
        }


        // Set our string.
        str = source;
    }

    return ch;
#endif
}

inline char32_t nextchar_utf32(const char32_t *&str)
{
    assert(str != NULL);

    char32_t ch = *str;

    if (ch != 0)
    {
        ++str;
    }

    return ch;
}




/**
*   \brief                Retrieves the next character in a string and moves the pointer to the start of the next character.
*   \param  str [in, out] Pointer to the string to retrieve the character from.
*   \return               The character that was being pointed to by \c str.
*
*   \remarks
*       If this function returns NULL, the null terminator was retrieved. When this occurs, the string
*       is _not_ moved forward to the next character (there is no characters after the null terminator).
*/
inline char32_t nextchar(const char *&str)
{
    return nextchar_utf8(str);
}
inline char32_t nextchar(const char16_t *&str)
{
    return nextchar_utf16(str);
}
inline char32_t nextchar(const char32_t *&str)
{
    return nextchar_utf32(str);
}
inline char32_t nextchar(const wchar_t *&str)
{
    switch (sizeof(wchar_t))
    {
    case 2: return nextchar_utf16((const char16_t *&)str);
    case 4: return nextchar_utf32((const char32_t *&)str);
    }

    return nextchar_utf8((const char *&)str);
}

template <typename T>
inline char32_t nextchar(T *&str)
{
    return nextchar((const T *&)str);
}


/**
*   \brief                Retrieves the next character in a string and moves the pointer to the start of the next character.
*   \param  str [in, out] Pointer to the string to retrieve the character from.
*   \return               The character that was being pointed to by \c str.
*
*   \remarks
*       If this function returns NULL, the start character is either larger or equal to the end
*       pointer. When this occurs, the start pointer is _not_ modified.
*/
template <typename T>
inline char32_t nextchar(reference_string<T> &str)
{
    if (str.start >= str.end)
    {
        return NULL;
    }

    return nextchar(str.start);
}


}

#endif // DRSL_NEXTCHAR
