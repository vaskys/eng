#version 330 core

in vec2 UVLeftTop;
in vec2 UVLeftBottom;

in vec2 UVRightTop;
in vec2 UVRightBottom;

uniform sampler2D depth_texture;

void main() {
  vec4 text_left_top = texture(depth_texture,UVLeftTop);
  vec4 text_left_bottom = texture(depth_texture,UVLeftBottom);
  vec4 text_right_top = texture(depth_texture,UVRightTop);
  vec4 text_right_bottom = texture(depth_texture,UVRightBottom);

  vec4 depth = vec4(text_left_top.x,text_right_top.x,text_left_bottom.x,text_right_bottom.x);

  float min_depth = min(min(depth.x,depth.y),min(depth.z,depth.w));
  float max_depth = max(max(depth.x,depth.y),max(depth.z,depth.w));

  vec2 pos = mod(gl_FragCoord.xy,2);
  int index = int(pos.x + pos.y);
  gl_FragDepth = index == 1 ? min_depth : max_depth;
}

