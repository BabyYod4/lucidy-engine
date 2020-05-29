#ifndef GRAPHIC_LIB_HPP
#define GRAPHIC_LIB_HPP

#include <glew/glew.h>

#include "data_types.hpp"
#include "logging.hpp"
#include "../settings.hpp"

namespace ly{

  static std::string _translateError(enum_t error) {
    switch (error) {
      case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
      case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
      case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
      case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW";
      case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW";
      case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
      case GL_CONTEXT_LOST:
        return "GL_CONTEXT_LOST";
      case GL_TABLE_TOO_LARGE:
        return "GL_TABLE_TOO_LARGE";
      default:
        return "UNDEFINED ERROR";
    };
  }

  static void _clearError() {
    while (glGetError() != GL_NO_ERROR);
  }

  static bool_t _logCall(cstring_t function, cstring_t file, int_t line) {
    bool_t noError = true;
    while (enum_t error = glGetError()) {
      std::cout << "[OpenGL Error] (" << _translateError(error) << ")" << "\r\n"
        << "\t" << "In function: " << function << "\r\n"
        << "\t" << "In file: " << file << "\r\n"
        << "\t" << "On line: " << line << std::endl;
      noError = false;
    }
    return noError;
  }

  #define DEBUG

  #if DEBUG_MODE == ENABLE
    #define GLCALL(x) _clearError(); x; ASSERT(_logCall(#x, __FILE__, __LINE__), ""); 
  #else
    #define GLCALL(x) x
  #endif


  static inline void initGraphicLib(){
      enum_t err = glewInit();
      if (err != GLEW_OK){
        ASSERT(false, "Could not initalize Graphics Library");
      }

      std::cout << "Graphics library initialized succesfully with OpenGL version " << glGetString(GL_VERSION) << std::endl;
  }

}

#endif // !GRAPHIC_LIB_HPP