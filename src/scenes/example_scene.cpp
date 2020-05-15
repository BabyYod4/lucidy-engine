#include "example_scene.hpp"


void ExampleScene::onInit(Window& t_window) {
    ImGui::CreateContext();
    t_window.claim([](window_tp* w){ ImGui_ImplGlfwGL3_Init(w, true); });
    ImGui::StyleColorsDark();
}

void ExampleScene::onCreate() {
    
}

void ExampleScene::onDestroy() {
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    std::cout << "Sucessfully destroying Example Scene" << std::endl;
}

void ExampleScene::onRender(const float_tp& t_delta) {
    
}

void ExampleScene::onDebugRender(Window& t_window) {
    ImGui_ImplGlfwGL3_NewFrame();
    ImGui::Text("Hello, world!");                           
    ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}
