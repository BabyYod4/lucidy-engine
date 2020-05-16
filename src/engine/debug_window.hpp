#ifndef DEBUG_WINDOW_HPP
#define DEBUG_WINDOW_HPP

#include "window.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

class DebugWindow{
public:
    DebugWindow();
    DebugWindow(Window& t_window);
    ~DebugWindow();

    void open();
    void close();
    void clear();
    void flush();

    void drawStart( const std::string& t_menuName );
    void drawEnd();

    void drawText( const std::string& t_text );
    bool drawButton( const std::string& t_name );
private:
    Window& m_window;
};

#endif /* DEBUG_WINDOW_HPP */
