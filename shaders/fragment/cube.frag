#version 410 core

in vec3 textureDir;

out vec4 FragColor;

uniform samplerCube cubemap;

void main()
{
    FragColor = texture(cubemap, textureDir);
}