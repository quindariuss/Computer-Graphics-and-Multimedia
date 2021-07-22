
#version 430 core

in vec4 bPosition;
in vec4 bNormal;

uniform mat4 mvp_transform;
uniform mat4 normal_transform;

out vec4 vNormal;


void
main()
{
    vNormal = normal_transform * bNormal;
    gl_Position =  mvp_transform * bPosition;
}
