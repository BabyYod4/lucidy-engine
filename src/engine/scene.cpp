#include "scene.hpp"


SceneController::SceneController(const SceneControllerSettings& t_settings, Window& t_window):
    m_settings( t_settings ),
    m_window( t_window ) 
{}

SceneController::~SceneController() {

    for (auto scene : m_scenes){
	    scene.second->onDestroy();
    }

}

void SceneController::add(const std::string& t_name, std::shared_ptr<Scene> t_scene) {
    if (std::find(m_sceneNames.begin(), m_sceneNames.end(), t_name) != m_sceneNames.end()){
        std::cerr << "Unable to add scene[" << t_name << "] because it already exists" << std::endl;
        return;
    }
    m_sceneNames.push_back(t_name);
    m_scenes.insert( std::make_pair(t_name, t_scene) );
}

void SceneController::remove(const std::string& t_name) {
    if (std::find(m_sceneNames.begin(), m_sceneNames.end(), t_name) == m_sceneNames.end()){
        std::cerr << "Unable to remove scene[" << t_name << "] because it does not exists" << std::endl;
        return;
    }
    m_scenes[t_name]->onDestroy();
    m_scenes.erase ( t_name );
    m_sceneNames.erase( std::remove( m_sceneNames.begin(), m_sceneNames.end(), t_name ), m_sceneNames.end() );
}

void SceneController::select(const std::string& t_name) {
    if (std::find(m_sceneNames.begin(), m_sceneNames.end(), t_name) == m_sceneNames.end()){
        std::cerr << "Unable to select scene[" << t_name << "] because it does not exists" << std::endl;
        return;
    }
    m_currentSceneName = t_name;
    m_currentScene = m_scenes[t_name];
    if (m_settings.resetTimerAfterEachScene){ glfwSetTime(0.0); }
}

std::string SceneController::getCurrent() {
    return m_currentSceneName;
}

void SceneController::run() {
    m_delta = glfwGetTime();
    m_currentScene->onCreate();
    m_currentScene->onEvent();
    m_currentScene->onRender(m_delta);
    m_currentScene->onUIRender(m_window);
    m_currentScene->onDebugRender(m_window);
}


void SceneController::init() {
    for (auto scene : m_scenes){
	    scene.second->onInit(m_window);
    }
}
