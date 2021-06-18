
#version 330 core

in vec4 bPosition;
in vec4 bColor;

out vec4 vColor;

void
main()
{
    vColor = bColor;
    gl_PointSize = 25.0;
    gl_Position = bPosition;
}
