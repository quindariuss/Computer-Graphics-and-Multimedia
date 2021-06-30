#version 450 core

out vec4 fColor;


uniform vec4 diffuse_color;

void main()
{
    fColor = diffuse_color;
}
