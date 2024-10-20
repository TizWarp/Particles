#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 fColor;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoords);// * vec4(fColor, 1.0f);
}
