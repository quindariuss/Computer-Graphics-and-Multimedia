#version 330 core

out vec4 fColor;

void main()
{
    // Dot Color
    // Cant add the rgb values 105, green 89, blue 205, and alpha 255 directly because the shader program takes a floating point in the range of 0 - 1
    fColor = vec4(0.41, 0.35, 0.80, 1.0);
}
