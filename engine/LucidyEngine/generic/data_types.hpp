#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <cstring>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace ly{

    typedef unsigned int uint_t;
    typedef int int_t;
    typedef float float_t;
    typedef double double_t;
    typedef bool bool_t;
    typedef uint_t enum_t;
    typedef std::string string_t;
    typedef const char* cstring_t;

    typedef glm::vec2 vec2_t;
    typedef glm::vec3 vec3_t;
    typedef glm::vec4 vec4_t;

    typedef struct range_t{ uint_t start; uint_t end; } range_t;

    typedef struct ratio_t{ uint8_t num; uint8_t denum; } ratio_t;

    static inline bool cstrEqual( cstring_t t_left, cstring_t t_right ){
        if ( std::strcmp(t_left, t_right) == 0 ) {return true;}
        return false;
    }

    static inline string_t vec2ToString( const vec2_t& t_data ){
        string_t buff = 
        " (" + std::to_string(t_data.x) + " ," + std::to_string(t_data.y) + " )";
        return buff;
    }

}

#endif // TYPES_HPP
