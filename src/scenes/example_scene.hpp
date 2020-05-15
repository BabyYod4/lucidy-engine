#ifndef EXAMPLE_SCENE_HPP
#define EXAMPLE_SCENE_HPP

#include "../engine/scene.hpp"

class ExampleScene : public Scene {
public:
    ExampleScene(const std::string& t_text);
    void onCreate(Window& t_window) override;
    void onDestroy() override;
    void onRender(const float_tp& t_delta) override;
    void onDebugRender(Window& t_window) override;
private:
    std::string m_text;

};

#endif // EXAMPLE_SCENE_HPP
