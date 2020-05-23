#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "gui_window.hpp"
#include "../generic/logging.hpp"

namespace ly{

    GuiWindow::GuiWindow(Window& t_window):
        m_window( t_window )
    {}

    GuiWindow::~GuiWindow() {
        close();
    }

    void GuiWindow::open() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer bindings
        m_window.claim( [](window_t* w){ ImGui_ImplGlfw_InitForOpenGL(w, false); } );
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void GuiWindow::close() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        std::cout << "GUI window Closed succesfully! " << std::endl;
    }

    void GuiWindow::clear() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void GuiWindow::flush() {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable){
            // window_t* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();

            m_window.claim( [](window_t* w){ glfwMakeContextCurrent(w); } );
        }
    }

    void GuiWindow::drawStart(cstring_t t_menuName) {
        ImGui::Begin( t_menuName );
    }

    void GuiWindow::drawEnd() {
        ImGui::End();
    }

    void GuiWindow::drawText(cstring_t t_text) {
        ImGui::Text( t_text );
    }

    bool GuiWindow::drawButton(cstring_t t_name) {
        return ImGui::Button( t_name ) ;
    }

}
