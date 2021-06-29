
#version 430 core

in vec4 bPosition;
in vec4 bNormal;

uniform mat4 mv_transform;
uniform mat4 p_transform;
uniform mat4 normal_transform;

out vec4 vNormal;
out vec4 vPosition;


void
main()
{
    vNormal = normal_transform * bNormal;
    vPosition = mv_transform * bPosition;
    gl_Position =  p_transform * vPosition;
}
