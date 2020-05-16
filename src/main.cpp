#include <scenes/example_scene.hpp>
#include <engine/scene_controller.hpp>

int main(void)
{
    auto messageBus = std::make_shared<MessageBus>();

    Window window( WindowSettings{1280, 720, "The Wonders of Mazalt", 1} );
    auto debugWindow = std::make_shared<DebugWindow>(window);

    SceneController controller( debugWindow );
    auto scene1 = std::make_shared<ExampleReceiverScene>(debugWindow, messageBus, "Scene text 1");
    auto scene2 = std::make_shared<ExampleSenderScene>(debugWindow, messageBus, "Scene text 2");

    controller.add( "scene1", scene1 );
    controller.add( "scene2", scene2 );
    // controller.select( "scene1" );

    while (!window.isClosed())
    {
        window.clear();
        debugWindow->clear();

        controller.run();
        
        debugWindow->flush();
        window.flush();

        messageBus->notify();
    }

    return 0;
}


