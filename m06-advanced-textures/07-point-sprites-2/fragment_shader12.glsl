#version 430 core

out vec4 fColor;



void main()
{
    
    const vec4 color1 = vec4(0.6, 0.0, 0.0, .5);
    const vec4 color2 = vec4(0.9, 0.7, 1.0, 1.0);

    vec2 temp = gl_PointCoord - vec2(0.5);
    float f = dot(temp, temp);  // square of the distance of the fragment from the center of the point

    float t = 0.25;


    if(f > t) {
//        fColor = vec4(1.0, 1.0, 0.0, 1.0);
        discard;
    } else {
        fColor = mix(color1, color2, smoothstep(0.1, t, f));
    }

//    fColor = vec4(gl_PointCoord, 0, 1);  // debugging, see if gl_PointCoord is working
}
