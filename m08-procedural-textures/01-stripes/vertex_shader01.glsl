
#version 430 core

in vec4 bPosition;
in vec4 bNormal;
in vec2 bTextureCoord;

uniform mat4 mv_transform;
//uniform mat4 v_transform;
uniform mat4 p_transform;
uniform mat4 normal_transform;

out vec4 vNormal;
out vec4 vPosition;
out vec2 vTextureCoord;


void
main()
{
    vTextureCoord = bTextureCoord;
    vNormal = normal_transform * bNormal;
    vPosition = mv_transform * bPosition;
    gl_Position =  p_transform * vPosition;
}
