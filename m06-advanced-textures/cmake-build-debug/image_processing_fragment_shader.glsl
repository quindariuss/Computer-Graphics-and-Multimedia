#version 430 core

out vec4 fColor;

in vec2 vTextureCoord;

uniform sampler2D  sampler;
uniform int fb_size;

void main()
{

    vec2 tc = vTextureCoord;
    vec4 base_color = texture(sampler, vTextureCoord);

    // unchanged
    fColor = base_color;


    // just red.  Uncomment this next line to see the result of a red filter
//    fColor = vec4(base_color.r, 0.0, 0.0, 1.0);
    // uncomment this next line to see a blue filter, but using green to display it.
//     fColor = vec4(0.0, base_color.b, 0.0, 1.0);

//     gray scale based on red only.  uncomment the next line to see it
//     fColor = vec4(base_color.r, base_color.r, base_color.r, 1.0);

    // negative colors.  Uncomment the next line to see it
//      fColor = vec4(1.0 - base_color.r, 1.0 - base_color.g, 1.0 - base_color.b, 1.0);


    // luminance
    //https://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color
    //0.2126 * R + 0.7152 * G + 0.0722 * B
    float g = 0.2126*base_color.r + 0.7152*base_color.g + 0.0722*base_color.b;
    // uncomment this next line to see a luminance based image
//     fColor = vec4(g, g, g, 1.0);


    // to see the coded luminance example work, remove the space between the * and / at the end
    // of the following comment.  Put the space back in to remove the example
    /*  coded luminance * /

    if(g < 0.3)
        fColor = vec4(1,0,0,1);
    else if(g < 0.6)
        fColor = vec4(1,1,0,1);
    else
        fColor = vec4(0,1,0,1);
    /* */

    // coded luminance, computed
//     fColor = mix(vec4(0,1,0,1), vec4(0,0,1,1), g);

    // to see the simpler luminance example work, remove the space between the * and / at the end
    // of the following comment.  Put the space back in to remove the example
    /*  Simpler version of luminance * /
    float g2 = (base_color.r + base_color.g + base_color.b) / 3.0;
    fColor = vec4(g2, g2, g2, 1.0);
    /* */


    // distance between pixels in the texture
    float delta = 1.0 / fb_size;

    // to see the smoothing example work, remove the space between the * and / at the end
    // of the following comment.  Put the space back in to remove the example
    /*  smoothing  * /
    vec4 s1 = texture(sampler, tc + vec2(delta,0));
    vec4 s2 = texture(sampler, tc + vec2(0,delta));
    vec4 s3 = texture(sampler, tc + vec2(0,-delta));
    vec4 s4 = texture(sampler, tc + vec2(-delta,0));
    fColor = (s1 + s2 + s3 + s4) / 4.0;
    /*  */


    /* Larger neighborhood * /
    vec4 s = vec4(0,0,0,0);
    const int lim = 3;
    for(int i = -lim; i <= lim; i++ ) {
        for(int j = -lim; j <= lim; j++) {
            s += texture(sampler, tc + vec2(i*delta, j*delta));
        }
    }
    fColor = s / ((2*lim+1)*(2*lim+1));
    /*  */


    // sobel derivative
    /*
        . . .
        . . .
        x . .

        Location of the first sample
    */
    vec4 u1 = texture(sampler, tc + vec2(-delta, -delta));
    /*
        . . .
        x . .
        . . .

        Location of the second sample
    */

    // to see the sobel derivative example work, remove the space between the * and / at the end
    // of the following comment.  Put the space back in to remove the example
    /* sobel derivative  * /
    vec4 u2 = 2*texture(sampler, tc + vec2(-delta, 0));
    vec4 u3 = texture(sampler, tc + vec2(-delta, delta));
    vec4 t1 = -texture(sampler, tc + vec2(delta, -delta));
    vec4 t2 = -2*texture(sampler, tc + vec2(delta, 0));
    vec4 t3 = -texture(sampler, tc + vec2(delta, delta));
    vec4 sobel = (u1 + u2 + u3 + t1 + t2 + t3) / 8.0;
    float d1 = length(sobel.xyz);

    u1 = texture(sampler, tc + vec2(-delta, -delta));
    u2 = 2*texture(sampler, tc + vec2(0, -delta));
    u3 = texture(sampler, tc + vec2(delta, -delta));
    t1 = -texture(sampler, tc + vec2(-delta, delta));
    t2 = -2*texture(sampler, tc + vec2(0, delta));
    t3 = -texture(sampler, tc + vec2(delta, delta));
    sobel = (u1 + u2 + u3 + t1 + t2 + t3) / 8.0;
    float d2 = length(sobel.xyz);

    float d = sqrt(d1*d1 + d2*d2);

    fColor = vec4(d, d, d, 1);
    /*  */
   
}
