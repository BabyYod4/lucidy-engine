#ifndef LIB_BASE_HPP
#define LIB_BASE_HPP

#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <cassert>
#include <iostream>
#include <cstdint>

#define ASSERT(x, msg) { if(!x){ std::cerr << msg << std::endl; assert(false); } }

typedef GLuint uint_tp;
typedef GLint int_tp;
typedef GLfloat float_tp;
typedef bool bool_tp;
typedef GLenum enum_tp;

typedef uint8_t uint8_tp;

typedef glm::vec2 vec2_tp;
typedef glm::vec3 vec3_tp;
typedef glm::vec4 vec4_tp;
typedef glm::mat4 mat4_tp;

static void initGraphicLib(){
    enum_tp err = glewInit();
    if (err != GLEW_OK){
      ASSERT(false, "Could not initalize Graphics Library");
    }

    std::cout << "Graphics library initialized succesfully with OpenGL version " << glGetString(GL_VERSION) << std::endl;
}

#endif // !LIB_BASE_HPP