#include "scene_controller.hpp"

SceneController::SceneController():
    m_currentSceneName(""),
    m_debugWindow(nullptr)
{}

SceneController::SceneController(std::shared_ptr<DebugWindow> t_debugWindow):
    m_currentSceneName(""),
    m_debugWindow(t_debugWindow)
{}

SceneController::~SceneController() {

    for (auto scene : m_scenes){
	    scene.second->onExit();
    }

}

void SceneController::add(const std::string& t_name, std::shared_ptr<Scene> t_scene) {
    if ( sceneExists(t_name) ){
        std::cerr << "Unable to add scene[" << t_name << "] because it already exists" << std::endl;
        return;
    }
    m_scenes.insert( std::make_pair(t_name, t_scene) );
}

void SceneController::remove(const std::string& t_name) {
    if ( t_name == m_currentSceneName ){
        std::cerr << "Unable to remove scene[" << t_name << "] because it is currently active" << std::endl;
        return;
    }

    if ( !sceneExists(t_name) ){
        std::cerr << "Unable to remove scene[" << t_name << "] because it does not exists" << std::endl;
        return;
    }

    m_scenes[t_name]->onExit();
    m_scenes.erase(t_name);

}

void SceneController::select(const std::string& t_name) {

    if ( t_name == m_currentSceneName ){
        std::cerr << "Unable to re-select scene[" << t_name << "] because it is currently active" << std::endl;
        return;
    }
    
    if ( !sceneExists(t_name) ){
        std::cerr << "Unable to select scene[" << t_name << "] because it does not exists" << std::endl;
        return;
    }
    if ( m_scenes.size() > 1 && m_currentSceneName != "" ){ m_scenes[m_currentSceneName]->onExit(); }
    m_currentSceneName = t_name;
    m_currentScene = m_scenes[t_name];
}

std::string SceneController::getActiveScene() {
    return m_currentSceneName;
}

void SceneController::run() {
    if( m_currentSceneName != ""){
        m_delta = glfwGetTime();
        m_currentScene->onEntry();
        m_currentScene->onEvent();
        m_currentScene->onRender(m_delta);
        m_currentScene->onExit();
    }

    if (ENABLE_SCENE_SELECTOR){
        drawSceneSelector();
    }
}

bool SceneController::sceneExists(const std::string& t_name) {
    for( const auto& scene: m_scenes ){
        if (scene.first == t_name){ return true; }
    }
    return false;
}

void SceneController::drawSceneSelector() {
    if (m_debugWindow == nullptr){ return; }

    m_debugWindow->drawStart("Scene Selector");
    m_debugWindow->drawText("Select a Scene");
  
    for( const auto& scene: m_scenes ){
        bool pressed = m_debugWindow->drawButton(scene.first);
        if ( pressed ){ select( scene.first ); } 
    }         

    m_debugWindow->drawEnd();
}

