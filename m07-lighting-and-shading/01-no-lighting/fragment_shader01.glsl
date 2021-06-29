#version 430 core

/*
    Uses the ambient_color passed from the driver to color the fragment

*/

out vec4 fColor;

uniform vec4 ambient_color;

void main()
{
    fColor = ambient_color;
}
