#ifndef SCENE_HPP
#define SCENE_HPP

#include "../types/data_types.hpp"

namespace ly{

class Scene{
public:
    virtual void onEntry(){};
    virtual void onExit(){};
    virtual void onRender(const float_t& t_delta) = 0;
    virtual void onEvent(){};
protected:
    cstring_t selectScene;
};

}

#endif // SCENE_HPP
