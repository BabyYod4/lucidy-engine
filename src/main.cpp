#include <scenes/example_scene.hpp>

int main(void)
{
    Window window( WindowSettings{1280, 720, "The Wonders of Mazalt", 1} );
    SceneController controller;

    auto scene1 = std::make_shared<ExampleScene>("Scene text 1");
    auto scene2 = std::make_shared<ExampleScene>("Scene text 2");

    controller.add( "scene1", scene1 );
    controller.add( "scene2", scene2 );

    while (!window.isClosed())
    {
        window.clear();

        controller.run();
        
        window.flush();
    }

    return 0;
}


