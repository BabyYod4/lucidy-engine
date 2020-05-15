#ifndef WINDOW_CONTEXT_HPP
#define WINDOW_CONTEXT_HPP

#include "lib_base.hpp"
#include <glfw/glfw3.h>
#include <functional>
#include <utility>

typedef GLFWwindow window_tp;

typedef struct WindowSettings{
    uint_tp width;
    uint_tp height; 
    std::string windowName;
    int_tp swapInterval;
    vec2_tp openglVersion;
} WindowSettings;

class Window{

public:
    Window();
    Window(WindowSettings&& t_settings);
    ~Window();

    void init();
    void clear();
    void flush();
    void poll();
    void close();
    bool isClosed();

    void claim(const std::function<void(window_tp*)>& task);
    void setSettings(WindowSettings&& t_settings);
    WindowSettings getSettings();

private: 
    WindowSettings m_settings;
    window_tp* m_window;

    void initGraphicLib();

};

#endif // !WINDOW_CONTEXT_HPP