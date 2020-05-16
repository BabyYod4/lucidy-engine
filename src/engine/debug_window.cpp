#include "debug_window.hpp"

DebugWindow::DebugWindow(Window& t_window):
    m_window( t_window )
{
    open(); 
}

DebugWindow::~DebugWindow() {
    close();
}

void DebugWindow::open() {
    ImGui::CreateContext();
    m_window.claim( [](window_tp* w){ ImGui_ImplGlfwGL3_Init(w, true); } );
    ImGui::StyleColorsDark();
}

void DebugWindow::close() {
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    std::cout << "Sucessfully destroyed Debug Window" << std::endl;
}

void DebugWindow::clear() {
    ImGui_ImplGlfwGL3_NewFrame();
}

void DebugWindow::flush() {
    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void DebugWindow::drawStart(const std::string& t_menuName) {
    ImGui::Begin( t_menuName.c_str() );
}

void DebugWindow::drawEnd() {
    ImGui::End();
}

void DebugWindow::drawText(const std::string& t_text) {
    ImGui::Text( t_text.c_str() );
}

bool DebugWindow::drawButton(const std::string& t_name) {
    return ImGui::Button( t_name.c_str() ) ;
}
