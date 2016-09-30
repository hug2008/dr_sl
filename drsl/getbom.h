/**
*   \file   getbom.h
*   \author Dave Reid
*   \brief  Header file for getbom() implementations.
*/
#ifndef __DRSL_GETBOM_H_
#define __DRSL_GETBOM_H_

#include "nextchar.h"

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
inline uchar32_t getbom(T *str)
{
    T *temp;
    if (drsl::nextchar(temp) == 0xFEFF)
    {
        return 0xFEFF;
    }

    return 0;
}

}

#endif // __DRSL_GETBOM_H_
