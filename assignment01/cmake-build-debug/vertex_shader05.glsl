
#version 330 core
//Still nothing happens when you change the z to 1.5 and the pixel is still visible



void
main()
{
    gl_PointSize = 15.0;
    gl_Position = vec4(0,0,1.5,1);
}
