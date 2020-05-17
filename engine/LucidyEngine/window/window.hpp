#ifndef WINDOW_CONTEXT_HPP
#define WINDOW_CONTEXT_HPP

#include "../settings.hpp"
#include "../graphic_lib.hpp"

#include <functional>
#include <glfw/glfw3.h>

namespace ly{

    typedef GLFWwindow window_t;

    typedef struct WindowSettings{
        uint_t width;
        uint_t height; 
        cstring_t windowName;
        int_t swapInterval;
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

        void claim(const std::function<void(window_t*)>& task);
        void setSettings(WindowSettings&& t_settings);
        WindowSettings getSettings();

    private: 
        WindowSettings m_settings;
        window_t* m_window;
    };

}


#endif // !WINDOW_CONTEXT_HPP