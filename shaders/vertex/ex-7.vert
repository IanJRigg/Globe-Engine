#version 410 core

layout (location = 0) in vec3 aPos; // the position has attribute position 0
layout (location = 1) in vec3 aColor; // The color has attribute position 1
layout (location = 2) in vec2 aTexCoord; // The texture coordinate position 2

out vec2 TexCoord;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}