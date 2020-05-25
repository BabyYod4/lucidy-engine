#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "generic/data_types.hpp"

namespace ly{

/// Setting Values
#define DISABLE                                 0
#define ENABLE                                  1

/// Generic Settings
#define SCENE_SELECTOR                          ENABLE
const uint_t BATCH_VERTEX_BUFFER_SIZE =         1024*10e6;
const uint_t BATCH_INDEX_BUFFER_SIZE =          1024*10e6;


/// OpenGL Settings
#define OPENGL_VERSION_USE_COMPAT               DISABLE
const int_t OPENGL_VERSION_MAJOR =              4;
const int_t OPENGL_VERSION_MINOR =              1;

}

#endif /* SETTINGS_HPP */
