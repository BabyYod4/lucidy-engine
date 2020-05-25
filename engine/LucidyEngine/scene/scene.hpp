#ifndef SCENE_HPP
#define SCENE_HPP

#include "../generic/data_types.hpp"
#include "../settings.hpp"

namespace ly{

class Scene{
public:
    virtual void onEntry(){};
    virtual void onExit(){};
    virtual void onUpdate(const float_t& t_delta){};
    virtual void onGuiRender(){};

#if SCENE_SELECTOR == ENABLE
    cstring_t getSceneName(){ return m_name.c_str(); }
#else
    cstring_t getSceneName(){ return "enable sceneselector" }
#endif
protected:

#if SCENE_SELECTOR == ENABLE
    string_t m_name;
    void setSceneName(cstring_t t_name){ m_name = t_name; } 
#else
    void setSceneName(cstring_t t_name){}
#endif 

};

}

#endif // SCENE_HPP
