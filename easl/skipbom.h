/**
*   \file   skipbom.h
*   \author Dave Reid
*   \brief  Header file for skipbom() implementations.
*/
#ifndef __EASL_SKIPBOM_H_
#define __EASL_SKIPBOM_H_

#include "nextchar.h"

namespace easl
{

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
inline uchar32_t skipbom(T *&str)
{
    T *temp = str;
    if (easl::nextchar(temp) == 0xFEFF)
    {
        str = temp;
        return 0xFEFF;
    }

    return 0;
}

}

#endif // __EASL_SKIPBOM_H_
