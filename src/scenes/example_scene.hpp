#ifndef EXAMPLE_SCENE_HPP
#define EXAMPLE_SCENE_HPP

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include "../engine/scene.hpp"

class ExampleScene : public Scene {
public:
    void onInit(Window& t_window) override;
    void onCreate() override;
    void onDestroy() override;
    void onRender(const float_tp& t_delta) override;
    void onDebugRender(Window& t_window) override;
private:

};

#endif // EXAMPLE_SCENE_HPP
