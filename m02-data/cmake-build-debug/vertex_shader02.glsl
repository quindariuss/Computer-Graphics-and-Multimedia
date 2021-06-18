
#version 430 core

in vec4 vPosition;


void
main()
{
    gl_PointSize = 25.0;
    gl_Position = vPosition;
}
