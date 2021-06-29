#version 430 core

out vec4 fColor;

in vec4 vNormal;

void main()
{
    fColor = abs(vec4(normalize(vNormal.rgb), 1.0));
}
