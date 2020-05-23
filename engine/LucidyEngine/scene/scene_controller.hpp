#ifndef SCENE_CONTROLLER_HPP
#define SCENE_CONTROLLER_HPP

#include "scene.hpp"
#include "../settings.hpp"
#include "../window/gui_window.hpp"
#include "../generic/stack.hpp"

namespace ly {

    class SceneController{
    public:

    #if SCENE_SELECTOR == ENABLE
        SceneController(GuiWindow& t_debugWindow);
    #else
        SceneController();
    #endif 

        ~SceneController();
        void addScene( Scene* t_scene );
        void addOverlay( Scene* t_scene );
        void run();

    private:
        float_t m_delta, m_currentTime, m_lastTime;
        SmartStack<Scene*> m_scenes;

    #if SCENE_SELECTOR == ENABLE
        GuiWindow& m_debugWindow;
        Scene* m_currentScene;
        void handleSceneSelector();
    #endif

    };

}

#endif /* SCENE_CONTROLLER_HPP */
