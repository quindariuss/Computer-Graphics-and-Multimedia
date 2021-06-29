#version 430 core

out vec4 fColor;

in vec4 vNormal;

void main()
{
    fColor = vec4(abs(normalize(vNormal.rgb)), 1.0);
}
