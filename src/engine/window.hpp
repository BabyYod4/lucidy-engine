#ifndef WINDOW_CONTEXT_HPP
#define WINDOW_CONTEXT_HPP

#include "settings.hpp"
#include <glfw/glfw3.h>

#include <functional>

typedef GLFWwindow window_tp;

typedef struct WindowSettings{
    uint_tp width;
    uint_tp height; 
    std::string windowName;
    int_tp swapInterval;
} WindowSettings;

class Window{

public:
    Window();
    Window(WindowSettings&& t_settings);
    ~Window();

    void open();
    void close();
    bool isClosed();

    void clear();
    void flush();

    void claim(const std::function<void(window_tp*)>& task);
    void setSettings(WindowSettings&& t_settings);
    WindowSettings getSettings();

private: 
    WindowSettings m_settings;
    window_tp* m_window;
};

#endif // !WINDOW_CONTEXT_HPP