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
- Develop a geographic grid algorithm
- Develop a subdivision surfaces algorithm
- Come up with a quad? octo tree implementation for adjustable LOD
- Figure out how to texture the damn cube
- Figure out how to compress the face subdividing code
- Make IMGUI Compile into a separate static lib
- Make GLAD compile into a separate static lib
- Implement the angular vertex optimization to the cube map algorithm



## Open Questions
- Make IMGUI look better? Better font, and some color theory would go far
- Find a texturing library that can be used to render the earth (BlueMarble?)
- 