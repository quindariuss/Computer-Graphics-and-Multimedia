
#version 430 core

in vec4 bPosition;
in vec4 bNormal;

uniform mat4 transform;

out vec4 vNormal;

void
main()
{
    vNormal = bNormal;
    gl_Position = transform * bPosition;
}
