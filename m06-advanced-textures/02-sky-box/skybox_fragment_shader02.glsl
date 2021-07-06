#version 430 core

out vec4 fColor;


in vec4 vPosition;


uniform samplerCube  sampler;

void main()
{
    //fColor = vec4(vTextureCoord, 0.0, 1.0);
    //fColor = vColor;
    fColor = texture(sampler, vPosition.xyz);
    //fColor = vec4(normalize(vPosition).xyz,1.0);
    //fColor = texture(sampler, normalize(vPosition).xyz);
    //fColor = texture(sampler, vec3(.5, .5, .5));
   
}
