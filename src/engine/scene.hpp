#ifndef SCENE_HPP
#define SCENE_HPP

#include "window.hpp"

#include <memory>
#include <unordered_map>
#include <algorithm>

class Scene{
public:
    virtual void onEntry() = 0;
    virtual void onExit() = 0;
    virtual void onRender(const float_tp& t_delta) = 0;
    virtual void onEvent(){};
protected:
    std::string selectScene;
};

class SceneController{
public:
    SceneController();
    ~SceneController();

    void add( const std::string& t_name, std::shared_ptr<Scene> t_scene );
    void remove( const std::string& t_name );
    void select( const std::string& t_name );
    void run();

    std::string getActiveScene();

private:
    float_tp m_delta;

    std::string m_currentSceneName;
    std::shared_ptr<Scene> m_currentScene;
    std::unordered_map<std::string, std::shared_ptr<Scene>> m_scenes;

    bool sceneExists(const std::string& t_name);
    void drawSceneSelector();

};

#endif // SCENE_HPP
