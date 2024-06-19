#version 330 core

out vec4 FragColor;
in vec2 UV;

uniform sampler2D color_texture;
uniform sampler2D ocluder_texture;

uniform vec2 sun_pos;

uniform float decay=0.96815;
uniform float exposure=0.2;
uniform float density=0.926;
uniform float weight=0.18767;

const int NUM_SAMPLES = 100;


void ocluder() {
    FragColor = vec4(0.0);

    vec2 tc = UV;
    vec2 deltaTexCoord = tc - sun_pos.xy;

    deltaTexCoord *= 1.0 / float(NUM_SAMPLES) * density;

    float illuminationDecay = 1.0;
    vec4 color =texture(ocluder_texture, tc.xy);
    for(int i=0; i < NUM_SAMPLES ; i++)
    {
        tc -= deltaTexCoord;
        vec4 sample = texture(ocluder_texture, tc);
        sample *= illuminationDecay * weight;
        color += sample;
        illuminationDecay *= decay;
    }
    vec4 realColor = texture(color_texture, UV);
    FragColor = ((vec4((vec3(color.r, color.g, color.b) * exposure), 1)) + (realColor*(1.1)));
}


void main()
{
  ocluder();
} 
