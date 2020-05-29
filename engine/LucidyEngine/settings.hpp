#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "generic/data_types.hpp"

namespace ly{

/// Setting Values
#define DISABLE                                             0
#define ENABLE                                              1

/// Generic Settings
#define SCENE_SELECTOR                                      ENABLE
#define DEBUG_MODE                                          ENABLE

const size_t BATCH_RENDERER_BUFF_SIZE =                     4096;
const ratio_t BATCH_RENDERER_VB_RATIO =                     { 1, 2 };
const ratio_t BATCH_RENDERER_IB_RATIO =                     { 1, 2 };


/// OpenGL Settings
#define OPENGL_VERSION_USE_COMPAT                           DISABLE
const int_t OPENGL_VERSION_MAJOR =                          4;
const int_t OPENGL_VERSION_MINOR =                          1;

}

#endif /* SETTINGS_HPP */
