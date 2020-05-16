#include "window.hpp"
#include <utility>


Window::Window() {}

Window::Window(WindowSettings&& t_settings) {
    m_settings = std::move( t_settings );
    open();
    initGraphicLib();
}

Window::~Window(){
    close();
}

void Window::open() {
    /* Initialize the library */
    if (!glfwInit()){ ASSERT(false, "Unable to initalize Window Library"); } 

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION.x);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION.y);
    m_window = glfwCreateWindow(m_settings.width, m_settings.height, m_settings.windowName.c_str(), NULL, NULL);
    
    if (!m_window) {
        glfwTerminate();
        ASSERT(false, "Unable to create Window");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(m_settings.swapInterval);
    std::cout << "Sucessfully created Window" << std::endl;
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::flush(){
    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);

    /* Poll for and process events */
    glfwPollEvents();
}

void Window::close() {
    glfwTerminate();
    std::cout << "Sucessfully destroyed Window" << std::endl;
}

bool Window::isClosed() {
    return glfwWindowShouldClose(m_window);
}

void Window::claim(const std::function<void(window_tp*)>& task) {
    task(m_window);
}

void Window::setSettings(WindowSettings&& t_settings) {
    m_settings = std::move( t_settings );
}

WindowSettings Window::getSettings() {
    return m_settings;
}


