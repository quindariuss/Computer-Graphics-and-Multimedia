
#version 430 core

in vec4 bPosition;
in vec4 bColor;

uniform mat4 transform;

out vec4 vColor;

void
main()
{
    vColor = bColor;
    gl_PointSize = 25.0;
    gl_Position = transform * bPosition;
//    gl_Position = bPosition;
}
