#include <scenes/example_scene.hpp>

int main(void)
{
    Window window( WindowSettings{1280, 720, "The Wonders of Mazalt", 1, {4,5} } );

    SceneController controller( SceneControllerSettings{true}, window );

    auto exampleScene = std::make_shared<ExampleScene>();

    controller.add( "example", exampleScene );

    controller.init();
    controller.select("example");

    while (!window.isClosed())
    {
        window.clear();
        
        controller.run();

        window.flush();
    }

    return 0;
}


