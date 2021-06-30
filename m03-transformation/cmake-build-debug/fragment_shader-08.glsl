#version 450 core

out vec4 fColor;

in vec4 vColor;

uniform vec4 diffuse_color;

void main()
{
    fColor = diffuse_color * vColor;
}
