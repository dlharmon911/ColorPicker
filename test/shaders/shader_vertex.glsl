#version 330 core

in vec4 al_pos;
in vec4 al_color;
uniform mat4 al_projview_matrix;
out vec4 varying_color;

void main()
{
    varying_color = al_color;
    gl_Position = al_projview_matrix * al_pos;
}
