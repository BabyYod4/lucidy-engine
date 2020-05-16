#include "example_scene.hpp"

/// ExampleReceiverScene
ExampleReceiverScene::ExampleReceiverScene(
    std::shared_ptr<DebugWindow> t_debugWindow, 
    std::shared_ptr<MessageBus> t_messageBus, 
    const std::string& t_text
):
    BusNode( t_messageBus ),
    m_text(t_text),
    m_message("No Messages Received"),
    m_debugWindow(t_debugWindow)
{}

void ExampleReceiverScene::onRender(const float_tp& t_delta) {
    m_debugWindow->drawStart(m_text);
    m_debugWindow->drawText( m_message.c_str() );
    m_debugWindow->drawEnd();                      
}


void ExampleReceiverScene::onMessageReceive(Message& t_message) {
    std::string event = t_message.getEvent();
    std::cout << "ExampleReceiverScene[1] received: " << event << std::endl;
    m_message = event;
}
/// ===============================================================================

/// ExampleSenderScene
ExampleSenderScene::ExampleSenderScene(
    std::shared_ptr<DebugWindow> t_debugWindow, 
    std::shared_ptr<MessageBus> t_messageBus, 
    const std::string& t_text
):
    BusNode( t_messageBus ),
    m_text(t_text),
    m_debugWindow(t_debugWindow)
{
    
}

void ExampleSenderScene::onRender(const float_tp& t_delta) {
    m_debugWindow->drawStart(m_text);
    bool pressed = m_debugWindow->drawButton("Click ME to send time to Scene 1");
    if (pressed){ sendMessage( Message(t_delta) ); }
    m_debugWindow->drawEnd();    
}
/// ===============================================================================
