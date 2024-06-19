out vec4 FragColor;

in vec3 normal_out;
in vec2 UV;
in vec3 frag_pos;
in vec4 frag_pos_light_space;



uniform vec3 cam_pos;

#ifdef ma_texture_diffuse
uniform sampler2D texture_diffuse;
#endif
uniform vec3 diffuse_color;
uniform vec3 specular_color;
uniform float specular_power;

#ifdef ma_shading

struct Light
{
  vec3 pos;
  vec3 color;
  float sila;
  float ambient;
};

struct SpotLight {
  vec3 pos;
  vec3 direction;
  vec3 color;
  float ambient;

  float sila;
  float cut_off;
  mat4 light_space;
  float bias;
};


#define max_svetiel 4
uniform Light svetla[max_svetiel];
uniform int active_svetla;

#define max_spot_light 4
uniform SpotLight spot_lights[max_spot_light];
uniform sampler2D shadow_s[max_spot_light];
uniform int active_spot_lights;

uniform vec3 global_light_dir;
uniform vec3 global_light_color;
uniform bool global_light_status;
uniform float global_light_ambient;
uniform sampler2D global_light_shadow;

vec3 cal_light(vec3 color,Light svetlo,vec3 normal)
{
  vec3 ambient=svetlo.ambient * svetlo.color * color;

  vec3 light_smer=normalize(svetlo.pos- frag_pos);
  float diff = max(dot(normal,light_smer), 0.0);
  float distance=length(svetlo.pos-frag_pos);
  
  diff = diff *(svetlo.sila /  distance ) ;
  vec3 diffuse = svetlo.color * color * diff;
  
  vec3 view_dir = normalize(cam_pos - frag_pos);
  vec3 reflect_dir = reflect(-light_smer,normal);
  float spec = pow(max(dot(view_dir,reflect_dir),0.0f),specular_power);
  spec = spec * (svetlo.sila / distance);
  vec3 specular = svetlo.color * (spec * specular_color );

  color = diffuse + ambient + specular;
  return color;
}

vec3 cal_global_light(vec3 color,vec3 normal,float shadow)
{
  vec3 ambient= global_light_ambient * global_light_color * color;

 // vec3 light_dir = normalize(global_light_dir - frag_pos);
  vec3 light_dir = normalize(global_light_dir);
  float diff = max(dot(light_dir,normal), 0.0);

  vec3 diffuse = diff * global_light_color * color;


  vec3 view_dir = normalize(cam_pos - frag_pos);
  vec3 reflect_dir = reflect(-light_dir,normal);
  float spec = pow(max(dot(view_dir,reflect_dir),0.0f), specular_power);
  vec3 specular = global_light_color * (spec * specular_color );

  vec3 final = ( ambient + ( 1.0 - shadow ) * diffuse + specular ) ;
  return final;
}


vec3 cal_spot_light(vec3 color,vec3 normal,SpotLight svetlo,float shadow) {
  vec3 light_dir = normalize(svetlo.pos - frag_pos);
  float theta = dot(light_dir, normalize(-svetlo.direction));

  vec3 ambient= svetlo.ambient * svetlo.color * color;

  if(theta > svetlo.cut_off) {
    float diff = max(dot(normal,light_dir), 0.0);
    float distance=length(svetlo.pos-frag_pos);

    diff = diff * (svetlo.sila / distance);
    vec3 diffuse = color*diff*svetlo.color;

    vec3 view_dir = normalize(cam_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir,normal);
    float spec = pow(max(dot(view_dir,reflect_dir),0.0f),specular_power);
    spec = spec * (svetlo.sila / distance);
    vec3 specular = svetlo.color * (spec * specular_color );

    return (ambient + (1.0f - shadow) * diffuse + specular ) ;
//    return diffuse * (1.0f - shadow )+ ambient;
  }
  return ambient;
}




float cal_shadow(vec4 frag_pos_light,vec3 light_dir,vec3 normal,sampler2D shadow_map,float b) {
  vec3 proj_coords = frag_pos_light.xyz / frag_pos_light.w;
  proj_coords = proj_coords * 0.5 + 0.5;

  if(proj_coords.z > 1.0) {
    float shadow = 0.0;
    return shadow;
  }
  //float close_depth = texture(shadow_map,proj_coords.xy).r;
  float current_depth = proj_coords.z;

  float bias = max(b * (1.0 - dot(normal, light_dir)), b/10);  
  //float shadow = current_depth - bias > close_depth ? 1.0 : 0.0;
  float shadow = 0.0f;
  int sample = 1;
  vec2 texelSize = 1.0 / textureSize(shadow_map, 0);
    for(int x = -sample; x <= sample; ++x)
    {
        for(int y = -sample; y <= sample; ++y)
        {
            float close_depth = texture(shadow_map, proj_coords.xy + vec2(x, y) * texelSize).r; 
            if(current_depth > close_depth + bias )
                shadow +=1.0f;
        }    
    }
  shadow /= pow((sample * 2 + 1),2);
  return shadow;
}

uniform int fog_type;
uniform bool fog_status;
uniform float fog_start;
uniform float fog_end;
uniform float fog_density;
uniform vec3 fog_color;

float cal_linear_fog() {
  float p_distance = length(frag_pos - cam_pos);
  float range = fog_end - fog_start;
  float distance = fog_end - p_distance;
  float factor = distance / range;
  factor = clamp(factor,0.0f,1.0f);
  return factor;
}

float cal_exp_fog() {
  float p_distance = length(frag_pos - cam_pos);
  float ratio = 4.0f * p_distance / fog_end;
  float factor = exp(-ratio * fog_density);

  return factor;
}

#endif


void main()
{

  vec3 color;
#if defined(ma_texture_diffuse)
  {
    vec4 texture_color = texture(texture_diffuse,UV);
    if(texture_color.a < 0.1) {
      discard;
    }

    color=diffuse_color*vec3(texture_color);
  }
#else
  color=diffuse_color;
#endif
#if defined(ma_shading)
  {
    vec3 normal=normalize(normal_out);
    vec3 final_farba=vec3(0,0,0);

    if(global_light_status) {
      float shadow = cal_shadow(frag_pos_light_space,global_light_dir,normal,global_light_shadow,0.05f);
      final_farba+=cal_global_light(color,normal,shadow);
    }
    for(int i=0;i<active_svetla;i++)
      final_farba+=cal_light(color,svetla[i],normal);


    for(int i =0; i < active_spot_lights;i++) {
      vec4 frag_pos_light = spot_lights[i].light_space * vec4(frag_pos,1.0f);
      float shadow = cal_shadow(frag_pos_light,spot_lights[i].pos,normal,shadow_s[i],spot_lights[i].bias);
      final_farba+=cal_spot_light(color,normal,spot_lights[i],shadow);
    }

    if(fog_status) {
      float fog = 0;
      switch(fog_type) {
        case 0:
          fog = cal_linear_fog();
          break;
        case 1:
          fog = cal_exp_fog();
          break;
      }
      final_farba = mix(fog_color,final_farba,fog);
    }

    FragColor=vec4(final_farba,1.0f);
  }
#else
  FragColor=vec4(color,1.0);

#endif
}

