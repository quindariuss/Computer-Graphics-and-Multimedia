#version 330 core
// Changing the color to 105/255, 89/255, 205/255, and 255/255 made the color turn black so for some reason it will have turned all the values to zero

out vec4 fColor;

void main()
{
    fColor = vec4(105/255, 89/255, 205/255, 255/255);
}
