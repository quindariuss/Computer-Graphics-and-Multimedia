#version 430 core

out vec4 fColor;


in vec4 vNormal;
in vec4 vPosition;
in vec2 vTextureCoord;

uniform vec4 ambient_light;
uniform vec4 specular_light;
uniform vec4 diffuse_light;
uniform vec4 ambient_color;
uniform vec4 specular_color;
uniform vec4 diffuse_color;

uniform vec4 light_direction; // direction toward the light
uniform float specular_shininess;     // exponent for sharpening highlights
uniform float specular_strength;      // extra factor to adjust shininess

uniform sampler2D  sampler;

void main()
{

    vec4 texture_sample = texture(sampler, vTextureCoord);

    vec3 half_vector = normalize(normalize(-light_direction.xyz) - normalize(vPosition.xyz));
    
    vec4 vnn = normalize(vNormal);

    float diffuse_factor = max(0.0, dot(vnn, -normalize(light_direction)));
    float specular_factor = max(0.0, dot(vnn.xyz, half_vector));

    if (diffuse_factor == 0.0)
        specular_factor = 0.0;
    else
       specular_factor = pow(specular_factor, specular_shininess) * specular_strength;  // sharpen the highlight


    vec4 ambient_component = texture_sample * ambient_light;
    vec4 diffuse_component = diffuse_factor * texture_sample * diffuse_light;
    vec4 specular_component = specular_factor * specular_color * specular_light;

    vec4 total = ambient_component + diffuse_component + specular_component;

    fColor = vec4(total.rgb, 1.0);
//    fColor = texture_sample;
  
}
