#include "window.hpp"

Window::Window() {}

Window::Window(WindowSettings&& t_settings) {
    m_settings = std::move( t_settings );
    init();
}

Window::~Window(){
    close();
}

void Window::init() {
    /* Initialize the library */
    if (!glfwInit())
        ASSERT(false, "Unable to initalize Window Library");

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION.x);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION.y);
    m_window = glfwCreateWindow(m_settings.width, m_settings.height, m_settings.windowName.c_str(), NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        ASSERT(false, "Unable to create Window");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(m_settings.swapInterval);
    std::cout << "Window library initalized succesfully! " << std::endl;
    initGraphicLib();

    if (ENABLE_DEBUG_WINDOW){
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(m_window, true);
        ImGui::StyleColorsDark();
    }
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (ENABLE_DEBUG_WINDOW){
        ImGui_ImplGlfwGL3_NewFrame();
    }
}

void Window::flush(){

    if (ENABLE_DEBUG_WINDOW){
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
    }

    /* Swap front and back buffers */
    glfwSwapBuffers(m_window);

    /* Poll for and process events */
    glfwPollEvents();
}

void Window::close() {

    if (ENABLE_DEBUG_WINDOW){
        ImGui_ImplGlfwGL3_Shutdown();
        ImGui::DestroyContext();
        std::cout << "Sucessfully destroyed Debug Window" << std::endl;
    }

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

void Window::initGraphicLib() {
    enum_tp err = glewInit();
    if (err != GLEW_OK){
      ASSERT(false, "Could not initalize Graphics Library");
    }

    std::cout << "Graphics library initialized succesfully with OpenGL version" << glGetString(GL_VERSION) << std::endl;
}

