#ifndef SCENE_HPP
#define SCENE_HPP

#include "window.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>

class Scene{
public:
    virtual void onInit(Window& t_window) = 0;
    virtual void onCreate() = 0;
    virtual void onDestroy() = 0;
    virtual void onRender(const float_tp& t_delta) = 0;
    virtual void onUIRender(Window& t_window){};
    virtual void onDebugRender(Window& t_window){};
    virtual void onEvent(){};
};

typedef struct SceneControllerSettings{
    bool resetTimerAfterEachScene;
} SceneControllerSettings;

class SceneController{
public:
    SceneController(const SceneControllerSettings& t_settings, Window& t_window);
    ~SceneController();

    void add( const std::string& t_name, std::shared_ptr<Scene> t_scene );
    void remove( const std::string& t_name );
    void select( const std::string& t_name );
    void run();
    void init();

    std::string getCurrent();

private:
    float_tp m_delta;
    SceneControllerSettings m_settings;
    Window& m_window;

    std::string m_currentSceneName;
    std::shared_ptr<Scene> m_currentScene;
    
    std::vector<std::string> m_sceneNames;
    std::unordered_map< std::string, std::shared_ptr<Scene> > m_scenes;
};

#endif // SCENE_HPP
