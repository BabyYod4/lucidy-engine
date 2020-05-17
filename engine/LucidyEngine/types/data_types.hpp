#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <cstring>

namespace ly{

    typedef unsigned int uint_t;
    typedef int int_t;
    typedef float float_t;
    typedef bool bool_t;
    typedef uint_t enum_t;
    typedef std::string string_t;
    typedef const char* cstring_t;

    static inline bool cstrEqual( cstring_t t_left, cstring_t t_right ){
        if ( std::strcmp(t_left, t_right) == 0 ) {return true;}
        return false;
    }

;}

#endif // TYPES_HPP
