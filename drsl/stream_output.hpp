// Copyright (C) 2016 David Reid. See included LICENSE file.

#ifndef DRSL_STREAMOUTPUT
#define DRSL_STREAMOUTPUT

template <typename T>
inline std::basic_ostream<T> & operator << (std::basic_ostream<T> &stream, const drsl::slow_string<T> &str)
{
    return stream.write(str.c_str(), static_cast<std::streamsize>(str.length()));
}

template <typename T, typename U>
inline std::basic_ostream<T> & operator << (std::basic_ostream<T> &stream, const drsl::slow_string<U> &str)
{
    const U *temp = str.c_str();

    char32_t ch;
    while ((ch = drsl::nextchar(temp)) != '\0')
    {
        stream.put((T)ch);
    }

    return stream;
}


template <typename T>
inline std::basic_ostream<T> & operator << (std::basic_ostream<T> &stream, const drsl::reference_string<T> &str)
{
    return stream.write(str.start, static_cast<std::streamsize>(str.end - str.start));
}

template <typename T, typename U>
inline std::basic_ostream<T> & operator << (std::basic_ostream<T> &stream, const drsl::reference_string<U> &str)
{
    drsl::reference_string<U> temp = str;

    char32_t ch;
    while ((ch = drsl::nextchar(temp)) != '\0')
    {
        stream.put((T)ch);
    }

    return stream;
}




#endif // DRSL_STREAMOUTPUT
