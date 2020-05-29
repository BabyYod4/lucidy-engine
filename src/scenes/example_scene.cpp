#include "example_scene.hpp"
#include <LucidyEngine/generic/logging.hpp>
#include <LucidyEngine/generic/data_types.hpp>

namespace ly{

    /// ExampleReceiverScene
    ExampleReceiverScene::ExampleReceiverScene(
        GuiWindow& t_debugWindow, 
        MessageBus* t_messageBus, 
        cstring_t t_text
    ):
        BusNode( t_messageBus ),
        m_text(t_text),
        m_message("No Messages Received"),
        m_debugWindow(t_debugWindow)
    {
        setSceneName( t_text );
    }

    void ExampleReceiverScene::onGuiRender() {
        m_debugWindow.drawStart( m_text );
        m_debugWindow.drawText( m_message.c_str() );
        m_debugWindow.drawEnd();                      
    }


    void ExampleReceiverScene::onEvent(Message& t_message) {
        m_message =  t_message.getEvent();
        std::cout << "ExampleReceiverScene[1] received: " << m_message << std::endl;
    }
    /// ===============================================================================


    /// ExampleSenderScene
    ExampleSenderScene::ExampleSenderScene(
        GuiWindow& t_debugWindow, 
        MessageBus* t_messageBus, 
        cstring_t t_text
    ):
        BusNode( t_messageBus ),
        m_text(t_text),
        m_debugWindow(t_debugWindow)
    {
        setSceneName( t_text );
    }

    void ExampleSenderScene::onUpdate(const float_t& t_delta) { 
        m_delta = t_delta;
    }

    void ExampleSenderScene::onGuiRender(){
        m_debugWindow.drawStart( m_text );
        bool pressed = m_debugWindow.drawButton("Click ME");
        if (pressed){ sendMessage( Message(m_delta) ); }
        m_debugWindow.drawEnd();    
    }
    /// ===============================================================================


    /// ExampleMouseEventScene
    ExampleMouseScene::ExampleMouseScene(Window& t_window, GuiWindow& t_debugWindow):
        m_window(t_window),
        m_debugWindow(t_debugWindow)
    {
        setSceneName( "Mouse Event Scene" );
    }

    void ExampleMouseScene::onGuiRender(){
        m_debugWindow.drawStart( "Mouse Event Scene" );
        m_debugWindow.drawText( vec2ToString( m_window.getMousePos() ).c_str() );
        m_debugWindow.drawText( vec2ToString( m_window.getScrollLevel() ).c_str() );
        m_debugWindow.drawEnd();    
    }
    /// ===============================================================================

ExampleBRTScene::ExampleBRTScene():
    m_square(1.3f)
{
    setSceneName( "BRTCube Scene" );

    m_renderer.addTarget("cube", &m_cube);
    m_renderer.addTarget("square", &m_square);
    m_renderer.setDrawList( {"cube", "square" } );

    m_shader.addFile( string_t(SANDBOX_PATH) + "assets/shaders/v_square.glsl", GL_VERTEX_SHADER );
    m_shader.addFile( string_t(SANDBOX_PATH) + "assets/shaders/f_color.glsl", GL_FRAGMENT_SHADER );
    m_shader.init();
}

void ExampleBRTScene::onUpdate(const float_t& t_delta) {
    
    m_shader.bind();
    m_renderer.draw();
    
}

} // Namespace END

