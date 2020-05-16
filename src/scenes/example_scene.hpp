#ifndef EXAMPLE_SCENE_HPP
#define EXAMPLE_SCENE_HPP

#include "../engine/scene.hpp"
#include "../engine/debug_window.hpp"
#include "../engine/message_bus/bus_node.hpp"
#include <memory>

class ExampleReceiverScene : public Scene, public BusNode {
public:
    ExampleReceiverScene(std::shared_ptr<DebugWindow> t_debugWindow, std::shared_ptr<MessageBus> t_messageBus, const std::string& t_text);
    void onRender(const float_tp& t_delta) override;
    void onMessageReceive(Message& t_message) override;
private:
    std::string m_text;
    std::string m_message;
    std::shared_ptr<DebugWindow> m_debugWindow;

};

class ExampleSenderScene : public Scene, public BusNode {
public:
    ExampleSenderScene(std::shared_ptr<DebugWindow> t_debugWindow, std::shared_ptr<MessageBus> t_messageBus, const std::string& t_text);
    void onRender(const float_tp& t_delta) override;
private:
    std::string m_text;
    std::shared_ptr<DebugWindow> m_debugWindow;
};

#endif // EXAMPLE_SCENE_HPP
