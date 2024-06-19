#version 330 core

layout (location = 0 ) in vec3 position;
layout (location = 2 ) in vec2 uv;

uniform sampler2D depth_texture;


out vec2 UVLeftTop;
out vec2 UVLeftBottom;

out vec2 UVRightTop;
out vec2 UVRightBottom;

void main() {
  vec2 texel_size = 1.0 / textureSize(depth_texture,0);

  UVLeftTop = uv - 0.5 * texel_size;
  UVLeftBottom = UVLeftTop + vec2(0,texel_size.y);

  UVRightTop = UVLeftTop + vec2(texel_size.x,0);
  UVRightBottom = UVLeftTop + texel_size;

  gl_Position=vec4(position,1.0);
}

