#version 330 core

#define PI (3.1415927)
#define GAUSS_BLUR_DEVIATION (1.5/2.0) 
#define HALF_RES_BLUR_KERNEL_SIZE (3)
#define BLUR_DEPTH_FACTOR 0.5

in vec2 UV;

out vec4 FragColor;

uniform sampler2D color_texture;
uniform bool vertical ;
uniform float near_plane = 0.0f;
uniform float far_plane = 1000.0f;

float gaussian_weight(float offset, float deviation) {
	float weight = 1.0f / sqrt(2.0f * PI * deviation * deviation);
	weight *= exp(-(offset * offset) / (2.0f * deviation * deviation));
	return weight;
}

float linear_eye_depth(float depth_value) {
	float z = depth_value * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

vec4 bilateral_blur(vec2 direction, vec2 texel_size, int kernel_radius) {
	float deviation = kernel_radius / GAUSS_BLUR_DEVIATION;

	vec4 center_color = texture(color_texture, UV);
	vec3 color = center_color.xyz;
	
	float center_depth = linear_eye_depth(center_color.w);

	float weight_sum = 0;

	float weight = gaussian_weight(0, deviation);
	
	color *= weight;
	weight_sum += weight;
				
	for (int i = -kernel_radius; i < 0; i += 1) {
		vec2 position = UV + (direction * i) * texel_size;
		vec4 sample_color = texture(color_texture, position);
		float sample_depth = linear_eye_depth(sample_color.w);

		float depth_diff = abs(center_depth - sample_depth);
		float dfactor = depth_diff * BLUR_DEPTH_FACTOR;
		float w = exp(-(dfactor * dfactor));

		weight = gaussian_weight(i, deviation) * w;

		color += weight * sample_color.xyz;
		weight_sum += weight;
	}

	for (int i = 1; i <= kernel_radius; i += 1) {
		vec2 position = UV + (direction * i) * texel_size;
		vec4 sample_color = texture(color_texture, position);
		float sample_depth = linear_eye_depth(sample_color.w);

		float depth_diff = abs(center_depth - sample_depth);
		float dfactor = depth_diff * BLUR_DEPTH_FACTOR;
		float w = exp(-(dfactor * dfactor));
		
		weight = gaussian_weight(i, deviation) * w;

		color += weight * sample_color.xyz;
		weight_sum += weight;
	}

	color /= weight_sum;
	return vec4(color, 0.0);
}

vec4 blur13(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.411764705882353) * direction;
  vec2 off2 = vec2(3.2941176470588234) * direction;
  vec2 off3 = vec2(5.176470588235294) * direction;
  color += texture(image, uv) * 0.1964825501511404;
  color += texture(image, uv + (off1 / resolution)) * 0.2969069646728344;
  color += texture(image, uv - (off1 / resolution)) * 0.2969069646728344;
  color += texture(image, uv + (off2 / resolution)) * 0.09447039785044732;
  color += texture(image, uv - (off2 / resolution)) * 0.09447039785044732;
  color += texture(image, uv + (off3 / resolution)) * 0.010381362401148057;
  color += texture(image, uv - (off3 / resolution)) * 0.010381362401148057;
  return color;
}

vec4 blur9(sampler2D image, vec2 uv, vec2 resolution, vec2 direction) {
  vec4 color = vec4(0.0);
  vec2 off1 = vec2(1.3846153846) * direction;
  vec2 off2 = vec2(3.2307692308) * direction;
  color += texture(image, uv) * 0.2270270270;
  color += texture(image, uv + (off1 / resolution)) * 0.3162162162;
  color += texture(image, uv - (off1 / resolution)) * 0.3162162162;
  color += texture(image, uv + (off2 / resolution)) * 0.0702702703;
  color += texture(image, uv - (off2 / resolution)) * 0.0702702703;
  return color;
}

void main() {
  vec4 color = vec4(0.0f);
  vec2 texel_size = 1.0 / textureSize(color_texture,0);

  if(vertical) {
    color = bilateral_blur(vec2(1,0),texel_size,HALF_RES_BLUR_KERNEL_SIZE);
//    color = blur9(color_texture,UV,vec2(640,380),vec2(1,0));
  }
  else {
   color = bilateral_blur(vec2(0,1),texel_size,HALF_RES_BLUR_KERNEL_SIZE);
  //  color = blur9(color_texture,UV,vec2(640,380),vec2(0,1));
  }
  

  FragColor = color; 
}
