
#version 430 core

in vec4 bPosition;
in vec4 bNormal;

uniform mat4 transform;
uniform mat4 n_transform;
uniform mat4 mv_transform;

out vec4 vPosition;
out vec4 vNormal;

void
main()
{
    vPosition = mv_transform * bPosition;
    vNormal = n_transform * bNormal;
//    vNormal = bNormal;
    gl_Position = transform * bPosition;
}
