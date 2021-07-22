#version 430 core

out vec4 fColor;

in vec2 vTextureCoord;

uniform vec4 ambient_color;
uniform vec4 ambient_light;

void main()
{
    fColor = min(ambient_color * ambient_light, vec4(1.0));
//    fColor = ambient_light;
//    fColor = ambient_color;

}
