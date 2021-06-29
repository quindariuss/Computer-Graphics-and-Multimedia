#version 430 core

out vec4 fColor;

/*
  Texture coordinates passed from the vertex shader
  Interpolated over each triangle
*/
in vec2 vTextureCoord;

/*
  The sampler provides access to the texture data.
*/
uniform sampler2D  sampler;

void main()
{
  // get a sample from the texture and use that as the fragment color
  fColor = texture(sampler, vTextureCoord);
}
