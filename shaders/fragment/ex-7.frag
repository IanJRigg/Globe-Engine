#version 410 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

void main()
{
//    FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
//    FragColor = texture(texture1, TexCoord);
   FragColor = mix
   (
       texture(texture1, TexCoord),
       texture(texture2, TexCoord),
       mixValue
   );
}