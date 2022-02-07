#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 vertex_texcoord;
layout(location = 3) in vec3 vertex_normal;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(vertex_position.x, vertex_position.y, 1.0, 1.0);
    TexCoords = vertex_texcoord;
}