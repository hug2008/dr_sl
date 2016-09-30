/**
*   \file   removebom.h
*   \author Dave Reid
*   \brief  Header file for removebom() implementations.
*/
#ifndef DRSL_REMOVEBOM
#define DRSL_REMOVEBOM

#include "skipbom.h"

namespace drsl
{

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

#endif // DRSL_REMOVEBOM
