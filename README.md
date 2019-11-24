# Globe Engine
This is an exercise to aid in learning OpenGL, it is a set of C++ wrapper objects around the OpenGL object implementation.

There are several gotchas that come with wrapping OpenGL in C++. Many of them are noted here: https://www.khronos.org/opengl/wiki/Common_Mistakes

The major pitfalls are:
- Making sure that an OpenGL context is active in the thread of execution that is being called.
- Disallow copying and make all wrapper objects move-only


The following tools are used in conjunction with the project:
- Makefiles generated with CMake3
- Unit Testing provided with Catch2
- Document Generation provided with Doxygen


## TODOs
- Create a camera class
- Develop a subdivision surfaces algorithm
- Develop a cube map algorithm
- Develop a geographic grid algorithm
- Make IMGUI look better? Better font, and some color theory would go far
- Make IMGUI Compile into a separate static lib
- Make GLAD compile into a separate static lib
- Find a texturing library that can be used to render the earth
- Click and drag algorithm can be changed such that the camera is translating, not the globe. This can be used to adjust LOD as well
- 