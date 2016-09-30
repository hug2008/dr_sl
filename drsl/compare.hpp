/**
*   \file   compare.h
*   \author Dave Reid
*   \brief  Header file for compare() implementations.
*/
#ifndef DRSL_STRCMP
#define DRSL_STRCMP

namespace drsl
{

/**
*   \brief                  Compares two strings for equality.
*   \param  str1       [in] The first string to compare.
*   \param  str2       [in] The second string to compare.
*   \param  str1Length [in] The length in T's of the first string.
*   \param  str2Length [in] The length in T's of the second string.
*   \return                 0 if the two strings are equal; -1 if \c str1 is lower than \c str2; +1 otherwise.
*
*   \remarks
*       The comparison is case sensitive. "Hello" does not equal "HELLO".
*       \par
*       If the length of a string is unknown, but it is NULL terminated, set the length to -1.
*/
template <typename T, typename U>
inline int compare(const T *str1, const U *str2, size_t str1Length = -1, size_t str2Length = -1)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    int ret = 0;

    while (str1Length > 0 && str2Length > 0)
    {
        char32_t ch1 = nextchar(str1);
        char32_t ch2 = nextchar(str2);

        ret = ch1 - ch2;

        if (ret != 0 || ch2 == '\0')
        {
            break;
        }

        size_t width = charwidth<T>(ch2);
        str1Length -= width;
        str2Length -= width;
    }

    if (ret < 0)
    {
        return -1;
    }
    else if (ret > 0)
    {
        return 1;
    }

    return 0;
}

template <typename T, typename U>
inline int compare(const reference_string<T> &str1, const reference_string<U> &str2)
{
    return compare(str1.start, str2.start, length(str1), length(str2));
}




/**
*   \brief                     Determines if two strings are equal.
*   \param  str1          [in] The first string to compare.
*   \param  str2          [in] The second string to compare.
*   \param  caseSensitive [in] Specifies whether or not the comparison is case sensitive.
*   \param  str1Length    [in] The length in T's of the first string, not including the null terminator.
*   \param  str2Length    [in] The length in U's of the second string, not including the null terminator.
*   \return                    True if the two strings are equal; false otherwise.
*
*   \remarks
*       Both strings must be NULL terminated. By default, the comparison is case sensitive.
*/
// TODO: Should implement a T-only optimization. We can remove the charcount() checks at the very least.
template <typename T, typename U>
inline bool equal(const T *str1, const U *str2, bool caseSensitive = true, size_t str1Length = -1, size_t str2Length = -1)
{
    if (str1 == NULL || str2 == NULL)
    {
        return false;
    }

    // If the number of characters in the strings are different, they are not equal.
    // NOTE: This should probably be optimised out.
    if (charcount(str1, str1Length) != charcount(str2, str2Length))
    {
        return false;
    }

    // We need to grab the first characters first.
    char32_t ch1 = nextchar(str1);
    char32_t ch2 = nextchar(str2);

    if (caseSensitive)
    {
        while ((str1Length > 0 && ch1 != '\0') && (str2Length > 0 && ch2 != '\0'))
        {
            if (ch1 != ch2)
            {
                return false;
            }

            ch1 = nextchar(str1);
            ch2 = nextchar(str2);

            str1Length -= charwidth<T>(ch1);
            str2Length -= charwidth<U>(ch2);
        }
    }
    else
    {
        while ((str1Length > 0 && ch1 != '\0') && (str2Length > 0 && ch2 != '\0'))
        {
            if (tolower(ch1) != tolower(ch2))
		    {
			    return false;
		    }

            ch1 = nextchar(str1);
            ch2 = nextchar(str2);

            str1Length -= charwidth<T>(ch1);
            str2Length -= charwidth<U>(ch2);
        }
    }

	return true;
}


// Optimized case. The function can be simplified and should be more efficient when both
// strings are the same type.
template <typename T>
inline bool equal(const reference_string<T> &str1, const reference_string<T> &str2, bool caseSensitive = true)
{
    // If the lengths are different, it's impossible for the strings to be the same. Calculating
    // the lengths for reference strings is a fast operation, so this check is worth while. It
    // also simplifies the next part.
    size_t len = length(str1);
    if (len != length(str2)) {
        return false;
    }

    // If the internal pointers are the same, the strings are also the same.
    if (str1.start == str2.start && str1.end == str2.end) {
        return true;
    }

    if (caseSensitive) {
        for (size_t i = 0; i < len; ++i) {
            if (str1.start[i] != str2.start[len]) {
                return false;
            }
        }
    } else {
        for (size_t i = 0; i < len; ++i) {
            if (tolower(str1.start[i]) != tolower(str2.start[len])) {
                return false;
            }
        }
    }

    return true;
}


template <typename T, typename U>
inline bool equal(const reference_string<T> &str1, const reference_string<U> &str2, bool caseSensitive = true)
{
    return equal(str1.start, str2.start, caseSensitive, length(str1), length(str2));
}

template <typename T, typename U>
inline bool equal(const T *str1, const reference_string<U> &str2, bool caseSensitive = true, size_t str1Length = -1)
{
    return equal(str1, str2.start, caseSensitive, str1Length, length(str2));
}

template <typename T, typename U>
inline bool equal(const reference_string<T> str1, const U *str2, bool caseSensitive = true, size_t str2Length = -1)
{
    return equal(str1.start, str2, caseSensitive, length(str1), str2Length);
}
}

#endif // DRSL_STRCMP
