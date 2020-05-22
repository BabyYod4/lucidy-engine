#include "scene_controller.hpp"
#include "../generic/logging.hpp"

namespace ly {

#if SCENE_SELECTOR == ENABLE

    SceneController::SceneController(DebugWindow& t_debugWindow):
        m_delta(0.0f), m_currentTime(0.0f), m_lastTime(0.0f),
        m_debugWindow(t_debugWindow),
        m_currentScene(nullptr)
    {}

    void SceneController::handleSceneSelector() {
        m_debugWindow.drawStart("Scene Selector");
        m_debugWindow.drawText("Select a Scene");
        for( Scene* scene: m_scenes ){
            bool pressed = m_debugWindow.drawButton( scene->getSceneName() );
            if ( pressed ){ 
                if (m_currentScene != nullptr) { m_currentScene->onExit(); }
                m_currentScene = scene;
                m_currentScene->onEntry();

                break;
            } 
        }         
        m_debugWindow.drawEnd();
    }

    void SceneController::run() {
        if (m_currentScene != nullptr){
            m_currentTime = glfwGetTime();
            m_delta = m_currentTime - m_lastTime;
            m_lastTime = m_currentTime;
            m_currentScene->onUpdate(m_delta);
        }

        handleSceneSelector();
    }

#else

    SceneController::SceneController():
        m_delta(0.0f), m_currentTime(0.0f), m_lastTime(0.0f)
    {}

    void SceneController::run() {
        for(Scene* scene: m_scenes){
            scene->onEntry();
            m_currentTime = glfwGetTime();
            m_delta = m_currentTime - m_lastTime;
            m_lastTime = m_currentTime;
            scene->onUpdate(m_delta);
            scene->onExit();
        }
    }


#endif

    void SceneController::addScene(Scene* t_scene) {
        m_scenes.pushFront(t_scene);
    }

    void SceneController::addOverlay(Scene* t_scene) {
        m_scenes.pushBack(t_scene);
    }


    SceneController::~SceneController() {
        for (Scene* scene : m_scenes){
            scene->onExit();
        }
    }


}

