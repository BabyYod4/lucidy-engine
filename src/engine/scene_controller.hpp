#ifndef SCENE_CONTROLLER_HPP
#define SCENE_CONTROLLER_HPP

#include "scene.hpp"
#include "debug_window.hpp"

#include <memory>
#include <unordered_map>
#include <algorithm>

class SceneController{
public:
    SceneController();
    SceneController(std::shared_ptr<DebugWindow> t_debugWindow);
    ~SceneController();

    void add( const std::string& t_name, std::shared_ptr<Scene> t_scene );
    void remove( const std::string& t_name );
    void select( const std::string& t_name );
    void run();

    std::string getActiveScene();

private:
    float_tp m_delta;
    std::shared_ptr<DebugWindow> m_debugWindow;

    std::string m_currentSceneName;
    std::shared_ptr<Scene> m_currentScene;
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;

    bool sceneExists(const std::string& t_name);
    void drawSceneSelector();

};

#endif /* SCENE_CONTROLLER_HPP */
