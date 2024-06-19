#ifndef VOLUMETRIC_SHADER_H
#define VOLUMETRIC_SHADER_H

#include "shader.h"

class VolumetricShader : BaseShader {
  public:
  VolumetricShader(string vertex_path,string fragment_path);
  ~VolumetricShader();

  void send_projection_inv(glm::mat4 proj);
  void send_view_inv(glm::mat4 view);
  void send_camera_pos(glm::vec3 pos);


  //void send_color_texture(unsigned int color_texture);
  void send_depth_texture(unsigned int depth_texture);

  void send_global_light_dir(glm::vec3 dir);
  void send_global_light_color(glm::vec3 color);
  void send_global_light_status(bool status);
  void send_global_depth_map(unsigned int mapa);
  void send_global_light_projection(glm::mat4 p);
  void send_global_light_view(glm::mat4 v);


  void send_spot_lights_shadow_map(unsigned int texture_id, int i);
  void send_spot_light_pos(glm::vec3 pos,int i);
  void send_spot_light_color(glm::vec3 color,int i);
  void send_spot_light_sila(float sila,int i);
  void send_spot_lights_cut_off(float cut,int i);
  void send_spot_lights_dir(glm::vec3 dir, int i);
  void send_spot_lights_view(glm::mat4 view, int i);
  void send_spot_lights_projection(glm::mat4 projection, int i);
  void send_spot_lights_pocet(unsigned int i);

  void send_scatter_value(float v);
  void send_time(float t);

  void send_volumetric_fog_status(int i);
  void send_volumetric_fog_denstiy(float i); 

  void register_uniforms();
  void use();
private:
  unsigned int projection_inv_uniform;
  unsigned int view_inv_uniform;
  unsigned int camera_pos_uniform;

  //unsigned int color_texture_uniform;
  unsigned int depth_texture_uniform;

  unsigned int spot_lights_shadow_map_uniform[4];
  unsigned int spot_lights_pos_uniform[4];
  unsigned int spot_lights_sila_uniform[4];
  unsigned int spot_lights_dir_uniform[4];
  unsigned int spot_lights_cutoff_uniform[4];
  unsigned int spot_lights_view_uniform[4];
  unsigned int spot_lights_projection_uniform[4];
  unsigned int spot_lights_color_uniform[4];
  unsigned int spot_lights_pocet_aktiv_uniform;


  unsigned int light_global_dir_uniform;
  unsigned int light_global_color_uniform;
  unsigned int light_global_status_uniform;
  unsigned int light_global_view_uniform;
  unsigned int light_global_projection_uniform;
  unsigned int global_light_depth_map_uniform;

  unsigned int scatter_value_uniform;
  unsigned int time_uniform;

  unsigned int volumetric_fog_status;
  unsigned int volumetric_fog_density_uniform;
};


#endif
