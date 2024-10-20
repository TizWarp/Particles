#version 330 core
layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec2 instance_pos;
layout (location = 3) in vec3 aColor;

out vec2 TexCoord;
out vec3 fColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{ 

    TexCoord = aTex;
    fColor = aColor;

    vec3 offset = vec3(instance_pos, 0.0f);

    gl_Position = projection * view * mat4(1.0f) *vec4(aVertex + offset, 1.0f);
}
