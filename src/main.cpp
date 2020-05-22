#include <LucidyEngine/generic/graphic_lib.hpp>

#include <LucidyEngine/scene/scene_controller.hpp>
#include <LucidyEngine/window/normal_window.hpp>
#include <scenes/example_scene.hpp>

int main(void)
{
    ly::MessageBus messageBus;

    ly::NormalWindow window( ly::WindowSettings{1280, 720, "The Wonders of Mazalt", 1, false} );
    ly::DebugWindow debugWindow( window );

    window.open();
    ly::initGraphicLib();
    debugWindow.open();

#if SCENE_SELECTOR == ENABLE
    ly::SceneController controller( debugWindow );
#else
    ly::SceneController controller;
#endif

    ly::ExampleReceiverScene scene1( debugWindow, &messageBus, "Receiver Scene" );
    ly::ExampleSenderScene scene2( debugWindow, &messageBus, "Sender Scene" );
    ly::ExampleMouseScene scene3( window, debugWindow );

    controller.addScene( &scene1 );
    controller.addScene( &scene2 );
    controller.addScene( &scene3 );

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