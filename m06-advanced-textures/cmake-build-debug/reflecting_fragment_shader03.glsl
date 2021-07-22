#version 430 core

out vec4 fColor;


in vec4 vPosition;
in vec4 vNormal;

uniform samplerCube  sampler;

void main()
{
    vec3 rfl = reflect(vPosition.xyz, normalize(vNormal.xyz));
    fColor = texture(sampler, rfl);
//    fColor = vec4(1,1,0,1);
//    fColor = vec4(normalize(vNormal.xyz), 1);
}
