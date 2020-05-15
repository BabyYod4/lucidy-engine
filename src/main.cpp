#include <scenes/example_scene.hpp>

int main(void)
{
    Window window( WindowSettings{1280, 720, "The Wonders of Mazalt", 1, {4,5} } );

    SceneController controller( SceneControllerSettings{true}, window );

    auto scene1 = std::make_shared<ExampleScene>("Scene text 1");
    auto scene2 = std::make_shared<ExampleScene>("Scene text 2");

    controller.add( "scene1", scene1 );
    controller.add( "scene2", scene2 );
    controller.select("scene2");

    ImGui::CreateContext();
    window.claim([](window_tp* w){ ImGui_ImplGlfwGL3_Init(w, true); });
    ImGui::StyleColorsDark();

    while (!window.isClosed())
    {
        window.poll();
        ImGui_ImplGlfwGL3_NewFrame();

        controller.run();

        ImGui::Begin("Another Window 2");
        ImGui::Text("Hello me workings");                           
        ImGui::End();

        window.clear();
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        window.flush();
    }

    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
    std::cout << "Sucessfully destroyed Example Scene" << std::endl;

    return 0;
}


