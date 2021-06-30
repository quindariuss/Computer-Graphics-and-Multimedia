
#version 450 core

in vec4 bPosition;

uniform mat4 transform;

void
main()
{
    gl_Position = transform * bPosition;
}
