Getting started with dr_sl.
==========================

Using dr_sl
-----------
dr_sl is a header library, so you need only include `drsl/drsl.h`. There is no need to link against any libraries.

To begin using dr_sl, simply include the file `<drsl/drsl.h>`, like so:
```c++
#include <drsl/drsl.h>
```

All of the functionality in dr_sl is under the `drsl` namespace.

dr_sl is made up of two main sections: a low level, C-like function section; and a higher level C++ `std::string`-like section. Having the library structured like this gives developers the most flexibility.

The C-like string manipulation routines work mostly the same as the standard C library equivalents. One major difference is that there is no difference in the name of the function for different string encodings. For example, to copy a string you simply use the `drsl::copy()` function for all types of string encodings - `char *` and `wchar_t *` alike.


Using UTF Encoding
------------------
dr_sl has support for UTF encoded strings. The supported encodings are UTF-8, UTF-16 and UTF-32. The table below illustrates the data types to use for the different encodings:

String Data Type | Encoding
---------------- | --------
`char*`          | UTF-8
`char16_t*`      | UTF-16
`char32_t*`      | UTF-32

So, a string declared as `char *` is encoded in UTF-8; a `char16_t *` string is encoded as UTF-16 and a `char32_t *` string is encoded as UTF-32.


`wchar_t` and UTF
-----------------
dr_sl assumes that any string contained as a `wchar_t` is UTF encoded. However, different platforms designate `wchar_t`'s with different sizes. On Windows, a `wchar_t` is 16-bit. On Linux, it's 32-bit. The specific encoding that dr_sl assumes depends on the size of a `wchar_t`. The table below illustrates the assumptions dr_sl makes.

`sizeof(wchar_t)` | UTF Encoding
----------------- | ------------
1                 | UTF-8
2                 | UTF-16
4                 | UTF-32

More information about `wchar_t` and UTF encodings can be found in the [TechnicalInfo Technical Information] wiki.


Examples
--------
Learning how to use dr_sl is best described with some examples. Check the [Examples] wiki for some good examples on using dr_sl.