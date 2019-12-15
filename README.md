# Globe Engine
This is an exercise to aid in learning OpenGL, it is a set of C++ wrapper objects around the OpenGL object implementation.

There are several gotchas that come with wrapping OpenGL in C++. Many of them are noted here: https://www.khronos.org/opengl/wiki/Common_Mistakes

The major notes are:
- Making sure that an OpenGL context is active in the thread of execution that is being called.
- Disallowing copying and make all wrapper objects move-only


The following tools are used in conjunction with the project:
- Makefiles generated with CMake3
- Unit Testing provided with Catch2
- Document Generation provided with Doxygen


## TODOs in order of priority
- Implement Latitude/Longitude and potentially WGS84 support
- Implement the angular vertex optimization to the cube map algorithm
- Come up with a quad? octo? tree implementation for adjustable LOD
- Figure out how to compress the face subdividing code

