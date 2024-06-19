#version 330 core

#define UPSAMPLE_DEPTH_THRESHOLD (0.5)

uniform sampler2D volumetric_texture;
uniform sampler2D color_texture;

uniform float near_plane = 0.1f;
uniform float far_plane = 1000.0f;

in vec2 UVCenter;
in vec2 UVLeftTop;
in vec2 UVLeftBottom;
in vec2 UVRightTop;
in vec2 UVRightBottom;

out vec4 FragColor;

float linear_depth(float depth_value) {
	float z = depth_value * 2.0 - 1.0;  
  return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

void main() {
  vec4 color = texture(color_texture,UVCenter);
  vec4 volumetric_color;

  vec4 tex_left_top = texture(volumetric_texture,UVLeftTop);
  vec4 tex_left_bottom = texture(volumetric_texture,UVLeftBottom);
  vec4 tex_right_top = texture(volumetric_texture,UVRightTop);
  vec4 tex_right_bottom = texture(volumetric_texture,UVRightBottom);

	vec4 high_res_depth = vec4(linear_depth(color.w));

	vec4 low_res_depth = vec4(
		linear_depth(tex_left_top.w),
		linear_depth(tex_right_top.w),
		linear_depth(tex_left_bottom.w),
		linear_depth(tex_right_bottom.w)
	);

	vec4 depth_diff = abs(low_res_depth - high_res_depth);
	float accum_diff = dot(depth_diff, vec4(1));


  if (accum_diff < UPSAMPLE_DEPTH_THRESHOLD) {
		volumetric_color = texture(volumetric_texture, UVCenter);
	} 
  else {
		float min_depth_diff = depth_diff[0];
		volumetric_color = tex_left_top;
		
		if (depth_diff[1] < min_depth_diff) {
			min_depth_diff = depth_diff[1];
			volumetric_color = tex_right_top;
		}
		
		if (depth_diff[2] < min_depth_diff) {
			min_depth_diff = depth_diff[2];
			volumetric_color = tex_left_bottom;
		}
		
		if (depth_diff[3] < min_depth_diff) {
			min_depth_diff = depth_diff[3];
			volumetric_color = tex_right_bottom;
		}
	}
	FragColor = volumetric_color + color;
}
