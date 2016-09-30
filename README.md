dr_sl
=====
dr_sl is a string library I wrote circa 2009 which I actually forgot about (originally
called easl). There's no point in letting it waste away so I figured I'd take the time
to restore it for modern compilers and fix a few issues. It's nothing special and a bit
over-engineered which tends to happen quite a bit when you're a young programmer! :)

The original intent for this library was to have it work seemlessly with UTF-8, UTF-16 and
UTF-32 encoding, however since writing this library I've never actually had any real use
for it so I'm not quite sure how useful this library would be.

This library is not optimal and has never been properly tested in any significant
real-world projects (at least that I'm aware of). Use it at your own risk.

Unlike my other libraries, this one is written in C++ and released under the MIT license.
The decision for this license was originally because Google Code didn't allow for public
domain. I may change it to public domain in the future if I feel the need.

Below is the original documentation with some small adjustments for rebranding and
whatnot. It's very possible this is a bit inaccurate and out of date, but I'll address
it those issues over time.

* * *

About dr_sl
===========

Introduction
------------
dr_sl is a C++ header library for working with strings.

It's primary goal is to ease the pain with using Unicode strings in C++. It has support for UTF-8, UTF-16 and UTF-32 string encodings.


Features
--------
Some of the notable features of the library include:

  * Easy to use
  * Low level C-style string manipulation functions
  * Higher level `std::string`-style string class
  * UTF encoded string manipulation routines
  * Generic API for all string encodings
  * Conversions between different encodings

Non-Features
------------
Some of the features dr_sl does not do. If your program needs any of the functionality
listed below, dr_sl is not useful:

  * Non-Unicode string manipulation
      * No support for UCS-2, etc. Only supports UTF-8, UTF-16 and UTF-32. Conversions
      between UCS and UTF encodings may be implemented in the future.
  * dr_sl is not optimized

dr_sl does not work with any string encoding other than UTF-8, UTF-16 and UTF-32. So,
for example, if you need to convert a UTF-16 string to a UCS-2 string, you will need to
perform the conversion either manually or via a separate library such as IBM's ICU. A
UCS/UTF converter may be implemented in the future.

Who is dr_sl For?
-----------------
dr_sl is useful for anyone who needs Unicode support in their applications. Applications
can still use dr_sl for non Unicode functionality. For example, if an application only
uses ASCII strings, they can still use dr_sl for it's miscellaneous string manipulation
routines and it's simple interface. UTF-8 strings are fully compatible with ASCII strings,
so ASCII-only applications can still make use of dr_sl.


Differences with IBM's ICU
--------------------------
[ICU](http://www.icu-project.org/) is a much larger project with a much broader scope than
dr_sl. dr_sl cares only for UTF-8, UTF-16 and UTF-32 formats. This restricts dr_sl from
only having to worry about the Unicode character set. On the other hand, ICU supports
pretty much every character set you can think of (though, they do recommend using Unicode
as much as possible). This makes ICU much more heavy-weight that dr_sl.

ICU also has much better localization support. Localization will slowly be improved in
dr_sl in the future.

ICU is probably a "better" solution at the moment, but this will change as dr_sl becomes
much more stable and adds additional features; in particular better localization.

If you're looking for an easy to use API, then dr_sl is definitely the way to go. Much of
the library is based on templates, so there is only a single generic API for every type of
character encoding. For example, converting a UTF-16 string to a UTF-8 string in dr_sl can
be done in a single line:

```c++
drsl::string utf8_string(some_utf16_string);
```


Getting Started
===============

Using dr_sl
-----------
dr_sl is a header library, so you need only include `drsl/drsl.h`. There is no need to link
against any libraries.

To begin using dr_sl, simply include the file `<drsl/drsl.h>`, like so:
```c++
#include <drsl/drsl.h>
```

All of the functionality in dr_sl is under the `drsl` namespace.

dr_sl is made up of two main sections: a low level, C-like function section; and a higher
level C++ `std::string`-like section. Having the library structured like this gives
developers the most flexibility.

The C-like string manipulation routines work mostly the same as the standard C library
equivalents. One major difference is that there is no difference in the name of the function
for different string encodings. For example, to copy a string you simply use the
`drsl::copy()` function for all types of string encodings - `char *` and `wchar_t *` alike.


Using UTF Encoding
------------------
dr_sl has support for UTF encoded strings. The supported encodings are UTF-8, UTF-16 and
UTF-32. The table below illustrates the data types to use for the different encodings:

String Data Type | Encoding
---------------- | --------
`char*`          | UTF-8
`char16_t*`      | UTF-16
`char32_t*`      | UTF-32

So, a string declared as `char *` is encoded in UTF-8; a `char16_t *` string is encoded as
UTF-16 and a `char32_t *` string is encoded as UTF-32.


`wchar_t` and UTF
-----------------
dr_sl assumes that any string contained as a `wchar_t` is UTF encoded. However, different
platforms designate `wchar_t`'s with different sizes. On Windows, a `wchar_t` is 16-bit. On
Linux, it's 32-bit. The specific encoding that dr_sl assumes depends on the size of a
`wchar_t`. The table below illustrates the assumptions dr_sl makes.

`sizeof(wchar_t)` | UTF Encoding
----------------- | ------------
1                 | UTF-8
2                 | UTF-16
4                 | UTF-32



Examples
========

Example 1: Simple Operations
----------------------------
This example demonstrates how to use traditional C-like string manipulation routines for
strings.

Code:
```c++
#include <drsl/drsl.h>
#include <iostream>

int main()
{
    char str1[1024];
    drsl::copy(str1, "Hello, World!");

    wchar_t *str2 = new wchar_t[1024];
    drsl::copy(str2, L"Hello!", 1024);

    std::cout << "String 1 length:  " << drsl::length(str1) << std::endl;
    std::cout << "String 1 content: " << str1 << std::endl << std::endl;

    std::wcout << L"String 2 length:  " << drsl::length(str2) << std::endl;
    std::wcout << L"String 2 content: " << str2 << std::endl;

    delete [] str2;

    return 0;
}
```

Output
```
String 1 length:  13
String 1 content: Hello, World!

String 2 length:  6
String 2 content: Hello!
```

Here the generic API is put to use. We can see that the same function is called for both
types of strings. So no more `strcpy()`/`wcscpy()` mixing and matching for C-style strings.

We've created one string with a static array and another with a dynamic array. We use the
same technique as the standard C++ library by not requiring us to specify the size of the
destination buffer for the static array. The size must be explicitly specified for the
dynamic array, however.


Example 2: Simple Conversion
----------------------------
This example demonstrates dr_sl's ability to convert between different types of strings. In
this example, we do a simple conversion between an archaic ANSI `char *` string and a
`wchar_t *` string. This type of conversion is convienient if some system function expects
the string as a `wchar_t *`.

Code:
```c++
#include <drsl/drsl.h>
#include <iostream>

int main()
{
    const char *source = "Hello, World!";

    size_t size = drsl::copysize<wchar_t>(source);
    wchar_t *dest = new wchar_t[size];
    drsl::copy(dest, source);

    std::wcout << L"Converted String: " << dest << std::endl;

    delete [] dest;

    return 0;
}
```

Output:
```
Converted String: Hello, World!
```

Here we are converting a `char *` string ("Hello, World!") to a `wchar_t *` string. We first
need to determine how many `wchar_t`'s we need to allocate in order to store the converted
string with a null terminator using `drsl::copysize()`. This is a function template that needs
the type we are converting to to be specified explicitly.

Once the memory for the new string has been allocated, we can perform the actual conversion
with `drsl::copy()`.

As you can see, copying a string with `drsl::copy()` will implicitly convert the string to the
appropriate format. Also, you can use `drsl::copysize()` to determine the size required for a
buffer for a regular string copy.


Example 3: Simple UTF Operations
--------------------------------
This example demonstrates some simple operations for working with UTF encoded strings. It
demonstrates some useful operations for working with UTF encoded strings such as iterating
through each character in the string.

Code:
```c++
#include <drsl/drsl.h>
#include <iostream>

int main()
{
    // UTF-8 string. Compatible with ASCII.
    const char *str = "I'm a UTF-8 string!";

    // Iterate through each character.
    const char *temp = str;
    char32_t ch;
    while ((ch = drsl::nextchar(temp)) != NULL)
    {
        std::cout << static_cast<char>(ch);
    }

    std::cout << std::endl;

    std::cout << "Number of char's in str1: " << 
        drsl::length(str) << std::endl;

    std::cout << "Number of characters in str1: " << 
        drsl::charcount(str) << std::endl << std::endl;

    return 0;
}
```

Output:
```
I'm a UTF-8 string!
Number of char's in str1: 19
Number of characters in str1: 19
```

Here we take a UTF-8 encoded string and perform some operations on it. The first thing we do
is iterate through each character in the string with `drsl::strnextchar()`. We need to create
a temporary pointer for the iterator so that we can reference the original string reliably.

We then demonstrate how the number of basic character units can be retrieved as well as the
number of characters. `drsl::length()` will always return the number of character units, and
not necessarily the number of characters. `drsl::charcount()` will always return the number of
characters. In this example, a "basic character unit" is a `char`; for a `char16_t *` string,
this would be a `char16_t`, etc.

The beauty of this example is that the original string can be changed to any other UTF
encoding (UTF-16 or UTF-32) and the program will still work without any modifications to the
rest of the code.


Example 4: Simple UTF Conversion
--------------------------------
This example will show how easy it is to convert a string between different UTF character
encodings and then back to a `wchar_t *` string.

Code:
```c++
#include <drsl/drsl.h>
#include <iostream>

int main()
{
    // UTF-8 string. Compatible with ASCII.
    const char *source = "Hello, World!";

    // Convert to UTF-16
    drsl::char16_t *dest = 
        new drsl::char16_t[drsl::copysize<drsl::char16_t>(source)];
    drsl::copy(dest, source);

    // Now convert back to wchar_t.
    wchar_t *final_dest = new wchar_t[drsl::copysize<wchar_t>(dest)];
    drsl::copy(final_dest, dest);

    std::wcout << L"String: " << final_dest << std::endl;

    delete [] dest;
    delete [] final_dest;

    return 0;
}
```

Output
```
String: Hello, World!
```

This example first converts a UTF-8 encoded string to a UTF-16 string. It then converts the
UTF-16string to a traditional `wchar_t` string. We can see that the process for converting
between UTF encodings is the same as converting between `char *` and `wchar_t *` strings.


Example 5: String Class
-----------------------
This simple example demonstrates the use of dr_sl's `std::string`-like string class.

Code:
```c++
#include <drsl/drsl.h>
#include <iostream>

int main()
{
    drsl::string some_utf8_string("Hello");
    drsl::wstring some_wchar_string(L", World!");

    // Append our wchar string to our UTF-8 string.
    some_utf8_string += some_wchar_string;
    
    // Create a UTF-16 and UTF-32 string from our UTF-8 string.
    // Converting between different encodings takes only a single line.
    drsl::string16 some_utf16_string(some_utf8_string);
    drsl::string32 some_utf32_string(some_utf16_string);
    

    // Output some results.
    std::cout << "some_utf8_string:  " << some_utf8_string << std::endl;
    std::cout << "some_utf16_string: " << some_utf16_string << std::endl;
    std::cout << "some_utf32_string: " << some_utf32_string << std::endl;

    return 0;
}
```

Output:
```
some_utf8_string:  Hello, World!
some_utf16_string: Hello, World!
some_utf32_string: Hello, World!
```

This example demonstrates how easy it is to work with different string encodings when using
dr_sl's string class(es). Here we first declare two strings of different encodings. The second
string, which is a `wchar_t *` string internally is appended to a `char *` (UTF-8) string.

The string is then converted to a UTF-16 string, which in turn is converted to a UTF-32 string.
The results are then printed to standard output to prove that it works. We can also see how
`operator <<` has been overloaded so that our custom strings can be easily printed to standard
output and any other `std::basic_ostream`.

In addition, it can be seen that the string classes are quite similar to `std::string`'s (but
not exactly the same). The `drsl::string` and `drsl::wstring` classes use a `char *` and
`wchar_t *` string internally, just like `std::string` and `std::wstring`. The UTF-16 string
is `drsl::string16` and the UTF-32 string is `drsl::string32`. A `drsl::string8` class is also
available which is simply an alias for `drsl::string` to match with `drsl::string16` and
`drsl::string32`.