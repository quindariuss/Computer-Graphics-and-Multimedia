
#version 330 core
//The point is still visable and the size doesnt change because with it moving along the z axis which will be distance from or to us we are still looking at it from a camera facing it directly.



void
main()
{
    gl_PointSize = 15.0;
    gl_Position = vec4(0,0,0.5,1);
}
