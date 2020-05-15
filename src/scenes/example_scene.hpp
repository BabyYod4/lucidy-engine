#ifndef EXAMPLE_SCENE_HPP
#define EXAMPLE_SCENE_HPP

#include "../engine/scene.hpp"

class ExampleScene : public Scene {
public:
    ExampleScene(const std::string& t_text);
    void onEntry() override;
    void onExit() override;
    void onRender(const float_tp& t_delta) override;
private:
    std::string m_text;

};

#endif // EXAMPLE_SCENE_HPP
