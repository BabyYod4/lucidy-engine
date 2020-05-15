#ifndef SCENE_HPP
#define SCENE_HPP

#include "window.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <memory>
#include <unordered_map>
#include <algorithm>

typedef struct SceneControllerSettings{
    bool_tp resetTimerAfterNewcene;
} SceneControllerSettings;

class Scene{
public:
    virtual void onCreate(Window& t_window) = 0;
    virtual void onDestroy() = 0;
    virtual void onRender(const float_tp& t_delta) = 0;
    virtual void onUIRender(Window& t_window){};
    virtual void onDebugRender(Window& t_window){};
    virtual void onEvent(){};
protected:
    std::string selectScene;
};

class SceneController{
public:
    SceneController(const SceneControllerSettings& t_settings, Window& t_window);
    ~SceneController();

    void add( const std::string& t_name, std::shared_ptr<Scene> t_scene );
    void remove( const std::string& t_name );
    void select( const std::string& t_name );
    void run();

    std::string getActiveScene();

private:
    bool_tp m_alreadyCreated;
    float_tp m_delta;
    SceneControllerSettings m_settings;
    Window& m_window;

    std::string m_currentSceneName;
    std::shared_ptr<Scene> m_currentScene;
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;

    bool sceneExists(const std::string& t_name);

};

#endif // SCENE_HPP
