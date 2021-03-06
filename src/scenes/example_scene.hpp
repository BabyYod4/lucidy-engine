#ifndef EXAMPLE_SCENE_HPP
#define EXAMPLE_SCENE_HPP

#include <LucidyEngine/shader/shader.hpp>
#include <LucidyEngine/scene/scene.hpp>
#include <LucidyEngine/window/gui_window.hpp>
#include <LucidyEngine/message_bus/bus_node.hpp>
#include <LucidyEngine/renderer/batch_renderer.hpp>
#include <LucidyEngine/renderer/targets/brt_cube.hpp>
#include <LucidyEngine/renderer/targets/brt_square.hpp>

#include <array>

namespace ly{

    class ExampleReceiverScene : public Scene, public BusNode {
    public:
        ExampleReceiverScene(GuiWindow& t_debugWindow, MessageBus* t_messageBus, cstring_t t_text);
        void onGuiRender() override;
        void onEvent(Message& t_message) override;
    private:
        cstring_t m_text;
        std::string m_message;
        GuiWindow& m_debugWindow;

    };

    class ExampleSenderScene : public Scene, public BusNode {
    public:
        ExampleSenderScene(GuiWindow& t_debugWindow, MessageBus* t_messageBus, cstring_t t_text);
        void onUpdate(const float_t& t_delta) override;
        void onGuiRender() override;
    private:
        cstring_t m_text;
        float_t m_delta;
        GuiWindow& m_debugWindow;
    };

    class ExampleMouseScene : public Scene {
    public:
        ExampleMouseScene(Window& t_window, GuiWindow& t_debugWindow);
        void onGuiRender() override;
    private:
        Window& m_window;
        GuiWindow& m_debugWindow;
    };

    class ExampleBRTScene : public Scene {
    public:
        ExampleBRTScene();
        void onUpdate(const float_t& t_delta) override;
    private:
        BatchRenderer m_renderer;
        BRTSquare m_square;
        BRTCube m_cube;
        Shader m_shader;
    };

}

#endif // EXAMPLE_SCENE_HPP
