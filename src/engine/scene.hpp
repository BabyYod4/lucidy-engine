#ifndef SCENE_HPP
#define SCENE_HPP

#include "lib_base.hpp"

class Scene{
public:
    virtual void onEntry(){};
    virtual void onExit(){};
    virtual void onRender(const float_tp& t_delta) = 0;
    virtual void onEvent(){};
protected:
    std::string selectScene;
};

#endif // SCENE_HPP
