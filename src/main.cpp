#include <LucidyEngine/scene/scene_controller.hpp>
#include <scenes/example_scene.hpp>

int main(void)
{
    ly::MessageBus messageBus;

    ly::Window window( ly::WindowSettings{1280, 720, "The Wonders of Mazalt", 1} );
    ly::DebugWindow debugWindow( window );

    ly::SceneController controller( debugWindow );
    ly::ExampleReceiverScene scene1( debugWindow, &messageBus, "Scene text 1" );
    ly::ExampleSenderScene scene2(debugWindow, &messageBus, "Scene text 2" );

    controller.add( "scene1", &scene1 );
    controller.add( "scene2", &scene2 );
    // controller.select( "scene1" );

    while (!window.isClosed())
    {
        window.clear();
        debugWindow.clear();

        controller.run();
        
        debugWindow.flush();
        window.flush();

        messageBus.notify();
    }

    return 0;
}


