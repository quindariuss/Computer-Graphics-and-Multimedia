
#version 430 core

in vec4 bPosition;

uniform mat4 transform;

out vec4 vPosition;

void
main()
{
    vPosition = bPosition;
    gl_Position = transform * bPosition;
}
