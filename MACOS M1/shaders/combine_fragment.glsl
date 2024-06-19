#version 330 core

out vec4 FragColor;
in vec2 UV;

uniform sampler2D texture_jedna;
uniform sampler2D texture_dva;

void main()
{
  vec4 jedna = texture(texture_jedna, UV);
  vec4 dva = texture(texture_dva, UV);
  FragColor = jedna + dva;

  // float depthValue = texture(color_texture, UV).r;
  // FragColor = vec4(vec3(depthValue), 1.0);
} 
