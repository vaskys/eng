#version 330 core

in vec2 UV;

out vec4 FragColor;

//uniform sampler2D color_texture;
uniform sampler2D depth_texture;

uniform float time;

struct SpotLight {
  vec3 pos;
  vec3 direction;
  vec3 color;

  float sila;
  float cut_off;

  mat4 view;
  mat4 projection;
};


#define max_spot_light 4
uniform SpotLight spot_lights[max_spot_light];
uniform sampler2D shadow_s[max_spot_light];
uniform int active_spot_lights;

uniform vec3 global_light_dir;
uniform vec3 global_light_color;
uniform bool global_light_status;
uniform mat4 global_light_projection;
uniform mat4 global_light_view;
uniform sampler2D global_light_shadow_map;

uniform vec3 cam_pos;
uniform mat4 cam_projection_inv;
uniform mat4 cam_view_inv;
uniform float scatter_value;

uniform int volumetric_fog_status;
uniform float volumetric_fog_density;

const int NUM_SAMPLES = 64;

float dither_pattern[16] = float[16] (
	0.0f, 0.5f, 0.125f, 0.625f,
	0.75f, 0.22f, 0.875f, 0.375f,
	0.1875f, 0.6875f, 0.0625f, 0.5625,
	0.9375f, 0.4375f, 0.8125f, 0.3125
);


vec3 world_pos_depth(float depth) {
  float z = depth * 2.0 - 1.0;
  vec4 clipSpacePosition = vec4(UV * 2.0 - 1.0, z, 1.0);
  vec4 viewSpacePosition = cam_projection_inv * clipSpacePosition;
  viewSpacePosition /= viewSpacePosition.w;
  vec4 worldSpacePosition = cam_view_inv * viewSpacePosition;
  return worldSpacePosition.xyz;
}


float mod289(float x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 mod289(vec4 x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 perm(vec4 x){return mod289(((x * 34.0) + 1.0) * x);}

float noise(vec3 p){
    vec3 a = floor(p);
    vec3 d = p - a;
    d = d * d * (3.0 - 2.0 * d);

    vec4 b = a.xxyy + vec4(0.0, 1.0, 0.0, 1.0);
    vec4 k1 = perm(b.xyxy);
    vec4 k2 = perm(k1.xyxy + b.zzww);

    vec4 c = k2 + a.zzzz;
    vec4 k3 = perm(c);
    vec4 k4 = perm(c + 1.0);

    vec4 o1 = fract(k3 * (1.0 / 41.0));
    vec4 o2 = fract(k4 * (1.0 / 41.0));

    vec4 o3 = o2 * d.z + o1 * (1.0 - d.z);
    vec2 o4 = o3.yw * d.x + o3.xz * (1.0 - d.x);

    return o4.y * d.y + o4.x * (1.0 - d.y);
}

float tri( float x ){ 
  return abs( fract(x) - .5 );
}

vec3 tri3( vec3 p ){
 
  return vec3( 
      tri( p.z + tri( p.y * 1. ) ), 
      tri( p.z + tri( p.x * 1. ) ), 
      tri( p.y + tri( p.x * 1. ) )
  );
}

float triNoise3d(in vec3 p, in float spd, in float time)
{
    float z=1.4;
	float rz = 0.;
    vec3 bp = p;
	for (float i=0.; i<=3.; i++ )
	{
        vec3 dg = tri3(bp*2.);
        p += (dg+time*spd);

        bp *= 1.8;
		z *= 1.5;
		p *= 1.2;
        //p.xz*= m2;
        
        rz+= (tri(p.z+tri(p.x+tri(p.y))))/z;
        bp += 0.14;
	}
	return rz;
}


float sample_fog(vec3 pos) {
//	return triNoise3d(pos * 2.2 / 8, 0.2, time)*0.75;
  return noise((pos / volumetric_fog_density) * time );
}


float cal_shadow(vec4 frag_pos_light,sampler2D shadow_map) {
  vec3 proj_coords = frag_pos_light.xyz / frag_pos_light.w;
  proj_coords = proj_coords * 0.5 + 0.5;

  if(proj_coords.z > 1.0) {
    float shadow = 0.0;
    return shadow;
  }
  float close_depth = texture(shadow_map,proj_coords.xy).r;
  float current_depth = proj_coords.z;

  float bias = 0.005;
  float shadow = current_depth - bias > close_depth ? 1.0 : 0.0;
  return shadow;
}

const float PI = 3.14159265359f;


float ComputeScattering(float lightDotView)
{
  float result = 1.0f - scatter_value * scatter_value;
  result /= (4.0f * PI * pow(1.0f + scatter_value * scatter_value - (2.0f * scatter_value) * lightDotView, 1.5f));
  return result;
  //return (1.0f - scatter_value * scatter_value) / (4.0f * PI * pow(1.0f + scatter_value * scatter_value - 2.0f * scatter_value * cosTheta, 1.5f));
}

vec3 volumetric_spot_light(vec3 frag_pos, SpotLight svetlo,sampler2D shadow_texture) {

	float dither_value = dither_pattern[ (int(gl_FragCoord.x) % 4)* 4 + (int(gl_FragCoord.y) % 4) ];

  vec3 volumetric  = vec3(0.0f);

  vec4 start= vec4(frag_pos,1.0f);
  vec4 end = vec4(cam_pos,1.0f);
  vec4 ray_dir = normalize(end - start);

  float step_length = length(end - start) / NUM_SAMPLES;
  vec4 step = ray_dir * step_length;
  vec4 ray_pos = start;

  ray_pos += step * dither_value;

  for(int i = 0; i < NUM_SAMPLES; i++) {
    vec4 ray_pos_light_space = svetlo.projection * svetlo.view * vec4(ray_pos.xyz,1.0f);
    float shadow = cal_shadow(ray_pos_light_space,shadow_texture);

    vec3 light_dir = svetlo.pos - ray_pos.xyz;
    light_dir = normalize(light_dir);

    float theta = dot(light_dir,normalize(-svetlo.direction));
    if(theta > svetlo.cut_off) {
      float fog = 1.0f;
      if(volumetric_fog_status == 1) {
        fog = sample_fog(ray_pos.xyz);
      }
      volumetric += fog *(1.0 - shadow) * ComputeScattering(dot(light_dir,svetlo.direction)) * step_length; 
      volumetric *= svetlo.color ;
    }
    ray_pos += step;
  }

  if(all(greaterThan(volumetric,vec3(1.0f)))) {
    return vec3(1.0f);
  }

  return volumetric ;
}

vec3 volumetric_global(vec3 frag_pos) {
	float dither_value = dither_pattern[ (int(gl_FragCoord.x) % 4)* 4 + (int(gl_FragCoord.y) % 4) ];

  vec3 volumetric  = vec3(0.0f);

  vec4 start= vec4(frag_pos,1.0f);
  vec4 end = vec4(cam_pos,1.0f);
  vec4 ray_dir = normalize(end - start);

  float step_length = length(end - start) / NUM_SAMPLES;
  vec4 step = ray_dir * step_length;
  vec4 ray_pos = start;

  ray_pos += step * dither_value;

  for(int i = 0; i < NUM_SAMPLES; i++) {
    vec4 ray_pos_light_space = global_light_projection * global_light_view * vec4(ray_pos.xyz,1.0f);
    float shadow = cal_shadow(ray_pos_light_space,global_light_shadow_map);

    vec3 light_dir = global_light_dir - ray_pos.xyz;
    light_dir = normalize(light_dir);

      float fog = 1.0f;
      if(volumetric_fog_status == 0) {
        fog = sample_fog(ray_pos.xyz);
      volumetric += fog * ComputeScattering(dot(light_dir,ray_dir.xyz)) * step_length; 
      }
    else if(volumetric_fog_status == 1) {
        fog = sample_fog(ray_pos.xyz);
        volumetric += fog * shadow * ComputeScattering(dot(light_dir,ray_dir.xyz)) * step_length; 
    }
    else {
      volumetric += fog * (1.0 - shadow ) * ComputeScattering(dot(light_dir,ray_dir.xyz)) * step_length; 
    }
    ray_pos += step;

  }

  if(all(greaterThan(volumetric,vec3(1.0f)))) {
    return vec3(1.0f);
  }
  return volumetric ;
}


void main() {

  float depth = texture(depth_texture, UV).r;
  vec3 frag_pos = world_pos_depth(depth);

  vec3 color = vec3(0.0f);

  if(global_light_status) {
    color +=volumetric_global(frag_pos) * 0.3f;
  }
  for(int i=0; i< active_spot_lights;i++) {
    color += volumetric_spot_light(frag_pos,spot_lights[i],shadow_s[i]);
  }


  vec4 xd = vec4(color,depth);
 // vec4 t = texture(color_texture,UV);
  //
  // vec4 f= xd + t;
  FragColor = xd;
}
