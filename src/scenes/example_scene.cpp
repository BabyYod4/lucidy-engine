#include "example_scene.hpp"

ExampleScene::ExampleScene(const std::string& t_text):
    m_text(t_text)
{}

void ExampleScene::onEntry() {
    
}

void ExampleScene::onExit() {
    
}

void ExampleScene::onRender(const float_tp& t_delta) {
    ImGui::Begin("Another Window");
    const char* name = m_text.c_str();
    ImGui::Text(name);                           
	ImGui::End();
}



