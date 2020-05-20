# Lucidy Engine 

![Main Logo Lucidy](https://user-images.githubusercontent.com/59289792/82435068-0ea8c400-9a94-11ea-9581-3ffc61f56a7c.png)

This is a personal effort to create a simple 3D graphics/game engine with modern C++ code that supports wide variety of graphics API's and platforms. 
In the frist stages of the engine I will primarly focus on supporting OpenGL 3.3 Core, but the code will be flexible to allow support for Vulkan and DX11 in the future. 
Another big feature that i want to add is the ability to mix up a fast computing library like CUDA or OpenCL with this engine that handles most of the physics based calculations. 

The engine is completely opensource and can be modified to your hand content. I real don't care what you do with it. 

## Reason to start this project

Personally I have some experience with game development in Unreal 4 and was always facinated about how the engine behind the scene works, which inturn sparked my intrest in Computer Graphics. 
This caused me to learn a bit about how a Graphics Pipeline works and how some common graphics libraries like OpenGL can be used to draw 3D objects on display, but right now i am done with what every tutorial/guide i could find online and want to put my skills to the test. 
I also like to improve my programming skills in C++ a bit so i thought this project might be a good place to start. I am no expert by any means and want to use this project just to improve my skills. 

Another reason I am starting this project is because i want to create an engine to create physics based simulation to simulate things like friction, pressure, velocity on 3D objects in space. 
When I initially thought about this simulation project, i was first aiming at just creating a simple 3D renderer and call it a day. But the more i looked at the requirements and features i wanted to add, the more it strated to look like a full blown game/graphics engine. 
So this caused me to tie up the knot and just start the project, hoping it will go somewhere in the future. 

I am also hoping I can use this engine in my follow up study of MSc Computer Graphics at TU delft (if my application is accepted ofc).

## What does the engine need to support in the first stage to be considered complete?

There a couple of things that really need to be added before i can call the first stage of the project complete, mainly:

- **Batch renderer**
- **Scene mechanics**
- **Message Bus**
- **Window manager**
- **Asset Loader**
- **IO manager**
- **Physics engine**
- **Scripting language**
- **Game debug tool**
- **Audio and SFX**

## How will I implemented the first stage?

In this first stage I want to mainly be using preexisting libraries and tools like GLFW, GLM, stb, etc to speed up the development process. 
But in saying this, i will make sure the code is scalable enough for me to implement my own libraries for mathematics, windows, io, etc in the future. 

The reason i want to create the basic libraries from scratch is because these fields also intrest me as a computer scientist and engineer. Another reason is so I can be sure that these core libraries are scalable enough to support a verity of systems and graphics libraries. I don't want to be depended on the support of others but be able to add support easily myself if i wanted in the future. 

Be aware none of the descision of the implementation methods are set in stone. As i have stated in the introduction, I am quite new to computer graphics, so if any of my 'implementations' seem crewd or stupid, feel free to give some **constructive** critism for better methods.

- *(if you reply like: "you suck, go kill yourself, your mom gay" i am probally not going to listen to your 'advice' )*


### Batch renderer

For the batch renderer i had the idea to just use one large dynamic vertex buffer and allow the content to be change during runtime. I figured this might be the most scalable and easy method to draw multple objects on the scene with a single draw call (i really dont want to use uniforms too much). But one thing that i really like to do, is setup the content of the vertex buffer like `CPU RAM`, where you have a `STACK` and `HEAP` that grow in opposite directions. 

Ofcourse this is just a single large array of data allocated at the stack during initalization and which can be change during runtime, but i would like the use of the engine/library to be able to allocate or even create 3D vertices during runtime and put them in the same vertex buffer in a manner that is managable and does not exceed the `GPU VRAM`. For example you could create a Renderer class and specify to allocate `n` GB of VRAM which is the limit the engine can use. 

To add and remove 3D objects from the display i want the user to be able to create so called `RenderTargets` which are in reality just objects that contain some meta data about the vertex layout, textures, meshes, ... and how it needs to be drawn. These `RenderTargets` can than be embedded in a list in the Batch renderer as pointers where the user can modify the vertex buffer layout by calling functions in the `RenderTarget` **not** by calling the Batch renderer it self. I figered it might be more intuative to do it like this, as you can more easily manage the objects being drawn on the screen. The only thing the batch renderer needs to is look at the list of `RenderTargets` it has and change its vertext buffer each iteration based on the meta data and setup of these `RenderTargets`. Examples of some `RenderTargets` are:

- Shapes: `RenderTargetCube`, `RenderTargetSphere`, `RenderTargetSpike`, etc
- 3D models that can be loaded from files like `fbx` and `obj`
- A series of lines that represent a wireframe   

### Scene mechanics

Let me first start by explaining what i mean with a Scene. I took this concept from an existing game engine name Godot which i realy liked and wanted to implement in some simple form. 

Imagine you are trying to create a game, there are two methods you could go about this:

1. Create one big state machine in the game loop where you can add or delete objects in the gameworld, handle movement, etc
2. Seperate each individual component of the game into its own class with its own initalization, run and delete process. This is in essence what a Scene is. A simple class with its own sub game loop that can be put into a list and be run in the real game loop. 

One advantage of using the second method is that you can more easily sepperate the logic of the game and also handle loading in multple levels. During the gameloop only whats in the currently selected scene will be loaded and drawn on the screen. If you for example wanted to load a new level or suddenly add some animation when something happens in the game, you could simple add this logic in its own scene and select that scene to play. So another way you could look at it is like a video player displaying a playlist of content where you can select what to play when. 

Another big thing i like about this method, that it is easier to debug mistakes and test code. For example lets say you created some physics objects but they dont move like you intend, then you can just load that specific scene of the game and debug it, or play around with it to see why its not working. 

### Message Bus 

The reason i want to implement a [MessageBus](https://www.enterpriseintegrationpatterns.com/patterns/messaging/MessageBus.html) instead of something like an event handler is that i have noticed in other graphical applications like `QT` or `SFML` it be much faster at sending messages between objectes. Another reason is that it is possible to extend this in the future to work in its own thread, meaning events send between `Scenes` won't take up time of the Batch renderer in the main loop. The last thing i want is the application to halt, because an event has not been received or is stalling in a Scene. 

### Window manager 

For the window manager i first intend to just create a wrapper on top of exisiting libraries like `GLFW` because this will suffice my needs. But to make the code a bit more portable i will also be creating a generic     `Window` interface that is used in the game engine instead of using the library code directly. Then i will create some private virtual functions that can be implemented by the different window libraries used. For example if i wanted to support something like DX11, i will be forces to use the `windows API`, but can still use the other code by just creating a new Window implementation. 

### Asset Loader 

The asset loader will be bare simple, just something to load in things like textures, meshes, files, `json`, music that are used in the code. For now i will also just stick with premade libraries like `stb`. The asset loader will be used by many different parts of the engine so i will spen a llot of time making sure it is fast and has propper error handling. 

### IO manager

Also going to keep it at a bare minimum, just using something like `GLFW` to manage IO from the keyboard, mouse and gamecontroller. One thing i am going to do in the name of abstraction is make sure that the game engine will use a generic interface instead of the library directly, where the implementation can use callbacks to change IO data in the IO interface. 

### Physics engine

For now i have no experience in physics but i am learning fast, so i will come up with an implementation as soon i understand how it works. 

### Scripting language

One thing i realy disliked about using scripting languages in game engines, is how little control you had on the game engine it self. You are mostly limited to some premade functions and have almost no control of the memmory. Therefor i will create my own scripting language which will be translated into native C++ code named "ly-script". This language will have combination `Javascript` and `C++` syntax which is greatly inspired by [Haxe](https://haxe.org/manual/types.html). Here a light-weight garbage collector will be used which does nothing more than create and destroy allocated objects when they are not used. But the user has te ability to use an optional advanced feature set of the language where they can allocate memmory on the heap and access game engine specific code during runtime and manage it them self if they like. 

This way you dont have to compile the game/graphic engine everytime you want to make a change but still have a bit more control. It wil **not** be an interpeted language, but instead will use a mechanic similar to Unreal Engine where you can write and code, compile that section with the library and than 'glue' them together. This way you only have to compile the game not the game engine.  I will begin with this feature on the very last part of development.

### Game debug tool

For now i just want to be able to print more detail command line output when things go sour, show messages about the game state on the screen. I will be initialy be using ImGui to do this, and just gdb. 

### Audio and SFX

Keep the trend with only the bare minimum alive, i will only focus on running background music in different layers and implement basic sound effect. I will probally use a premade library for this. 

# Development log

**20-05-2020**:

- Today i Added the basic functionality of the `SceneController`, `WindowManager`, `MessageBus` and `DebugTools`. 
For now i will keep it as if, because i don't think spending too much time on these aspects will add much on the engine. I would like to focus my attention and time on the Renderer and Physics. So this will be what i will focus next on. 
- I also tested the engine different target os's and made a simple cross platform workspace that can be used with `Linux`, `Windows` and `WSL`. This took up more time than i initially thought in `CMake`. It can be found [here](https://github.com/BabyYod4/opengl-vscode-cmake-template) 

