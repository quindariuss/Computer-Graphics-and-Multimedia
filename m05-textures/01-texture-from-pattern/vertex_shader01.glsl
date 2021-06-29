
#version 430 core

// each vertex has two attributes: position and texture coordinates
in vec4 bPosition;
in vec2 bTextureCoord;

// pass the texture coordinates to the fragment shader
out vec2 vTextureCoord;

void
main()
{
    // pass the texture coordinates to the fragment shader
    vTextureCoord = bTextureCoord;
    gl_Position = bPosition;
}
