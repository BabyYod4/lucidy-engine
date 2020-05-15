#include "example_scene.hpp"

ExampleScene::ExampleScene(const std::string& t_text):
    m_text(t_text)
{}

void ExampleScene::onCreate(Window& t_window) {
    // ImGui::CreateContext();
    // t_window.claim([](window_tp* w){ ImGui_ImplGlfwGL3_Init(w, true); });
    // ImGui::StyleColorsDark();
    
}

void ExampleScene::onDestroy() {
    // ImGui_ImplGlfwGL3_Shutdown();
    // ImGui::DestroyContext();
    // std::cout << "Sucessfully destroyed Example Scene" << std::endl;
}

void ExampleScene::onRender(const float_tp& t_delta) {
    
}

void ExampleScene::onDebugRender(Window& t_window) {
    ImGui::Begin("Another Window");
    const char* name = m_text.c_str();
    ImGui::Text(name);                           
	ImGui::End();
}


