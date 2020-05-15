#include "scene.hpp"


SceneController::SceneController(const SceneControllerSettings& t_settings, Window& t_window):
    m_alreadyCreated(false),
    m_settings( t_settings ),
    m_window( t_window ),
    m_currentSceneName("")
{}

SceneController::~SceneController() {

    for (auto scene : m_scenes){
	    scene.second->onDestroy();
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

    m_scenes[t_name]->onDestroy();
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
    if ( m_scenes.size() > 1 && m_currentSceneName != "" ){ m_scenes[m_currentSceneName]->onDestroy(); }
    m_currentSceneName = t_name;
    m_currentScene = m_scenes[t_name];
    m_alreadyCreated = false;
    if (m_settings.resetTimerAfterNewcene){ glfwSetTime(0.0); }
}

std::string SceneController::getActiveScene() {
    return m_currentSceneName;
}

void SceneController::run() {
    // m_delta = glfwGetTime();
    // if( !m_alreadyCreated ){
    //     m_currentScene->onCreate(m_window);
    //     m_alreadyCreated = true;
    // }
    // m_currentScene->onEvent();
    // m_currentScene->onRender(m_delta);
    // m_currentScene->onUIRender(m_window);
    m_currentScene->onDebugRender(m_window);
}

bool SceneController::sceneExists(const std::string& t_name) {
    for( const auto& scene: m_scenes ){
        if (scene.first == t_name){ return true; }
    }
    return false;
}

// void SceneController::initSceneSelector(Window& t_window) {
//         ImGui::CreateContext();
//         t_window.claim([](window_tp* w){ ImGui_ImplGlfwGL3_Init(w, true); });
//         ImGui::StyleColorsDark();
// }

// void SceneController::drawSceneSelector(Window& t_window) {
//     t_window.flush();
//     ImGui_ImplGlfwGL3_NewFrame();
//     ImGui::Text("Select Scene"); 

//     for( const auto& scene: m_scenes ){
//         const char* name = scene.first.c_str();
//         if ( ImGui::Button(name) ){
//             select( scene.first );
//         } 
//     }

//     ImGui::Render();
//     ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
//     t_window.clear();
// }

