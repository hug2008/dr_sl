// Copyright (C) 2016 David Reid. See included LICENSE file.

namespace drsl
{
/**
*   \brief           Retrieves the BOM from a given string.
*   \param  str [in] The string to retrieve the BOM from.
*   \return          0xFEFF if the BOM if found, 0 otherwise.
*
*   \remarks
*       This function will not modify the input string in any way. To retrieve the
*       BOM and move passed it, use skipbom() instead.
*/
template <typename T>
inline char32_t getbom(T *str)
{
    T *temp = str;
    if (drsl::nextchar(temp) == 0xFEFF)
    {
        return 0xFEFF;
    }

    return 0;
}

/**
*   \brief           Skips over the BOM of the string if it has one.
*   \param  str [in] The string whose BOM should be skipped over.
*   \return          The BOM if the string has one, or 0 if it doesn't.
*
*   \remarks
*       This function will move the input pointer to a point just past the BOM if
*       one is present. If there is no BOM, the pointer is not moved.
*/
template <typename T>
inline char32_t skipbom(T *&str)
{
    T *temp = str;
    if (drsl::nextchar(temp) == 0xFEFF)
    {
        str = temp;
        return 0xFEFF;
    }

    return 0;
}

/**
*   \brief                      Attaches the BOM to the start of the specified string.
*   \param  str       [in, out] The string to attach the BOM to.
*   \param  strSize   [in]      The size of the buffer pointed to by \c str.
*   \param  strLength [in]      The length in T's of the existing string pointed to by \c str, not including the null terminator.
*
*   \remarks
*       There must be enough room in the string buffer to store the BOM. In order
*       to determine how many T's are required to store the BOM, call charwidth().
*/
template <typename T>
inline void attachbom(T *str, size_t strSize = -1, size_t strLength = -1)
{
    // We need to determine how many T's our BOM is going to take up.
    size_t size = charwidth<T>((char32_t)0xFEFF);

    // Now we can move all of our character down one spot. First we need to get to
    // the end.
    T *temp = str;
    while (strLength > 0 && *temp != '\0')
    {
        --strLength;
        ++temp;
    }
    
    // temp is now positioned at the null terminator, so now we need to work our way backwards.
    while (temp != str)
    {
        for (unsigned short i = 0; i < size; ++i)
        {
            *(temp + size) = *temp--;

            if (temp == str)
            {
                *(temp + size) = *temp;
                break;
            }
        }
    }

    // Now we can set the BOM.
    writechar(str, 0xFEFF);
}

/**
*   \brief                Removes the BOM from the specified string if one is present.
*   \param  str [in, out] The string to remove the BOM from.
*/
template <typename T>
inline void removebom(T *str)
{
    T *temp = str;
    if (skipbom(temp) != 0)
    {
        // If we've made it here, the BOM was present, so we now want to
        // move our string down some spots.
        size_t bom_size = temp - str;

        while (*temp != '\0')
        {
            for (size_t i = 0; i < bom_size; ++i)
            {
                if (*temp == '\0')
                {
                    break;
                }

                *str = *temp;

                ++str;
                ++temp;
            }
        }

        // Null terminate it.
        *str = NULL;
    }
}
}