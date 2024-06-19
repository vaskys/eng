#version 330 core

out vec4 FragColor;
in vec2 UV;

uniform sampler2D color_texture;

void main()
{
    FragColor = texture(color_texture, UV);

    // float depthValue = texture(color_texture, UV).r;
    // FragColor = vec4(vec3(depthValue), 1.0);
} 
