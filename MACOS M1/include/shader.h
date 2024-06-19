#ifndef SHADER_H
#define SHADER_H

#include "config.h"

#include "mesh.h"
#include "animator.h"

typedef struct {
  Mesh *mesh;
  glm::mat4 global_transform;
  Animator *animator;
  bool has_bones;
}MESH_T;

class BaseShader
{
public:
  BaseShader(string vertex_path,string fragment_path);
  BaseShader(string vertex_kod,string fragment_kod,bool bruh);
  ~BaseShader();


  void send_float_uniform(const string name,float v);
  void send_int_uniform(const string name,int v);
  void send_vec3_uniform(const string name,glm::vec3 v);
  void send_mat4_uniform(const string name,glm::mat4 mat);
  void send_texture_uniforom(const string name,unsigned int texture_id);


  void use();
  virtual void register_uniforms();

  unsigned int get_id();


protected:
  void compile(string vertex_code,string fragment_code);
  unsigned int id;
};


class DefaultShader : public BaseShader
{
public:
  DefaultShader(string vertex_path,string fragment_path);
  DefaultShader(string vertex_code_i,string fragment_code_i,bool bruh);
  ~DefaultShader();

  void send_projection_uniform(glm::mat4 projection);
  void send_view_uniform(glm::mat4 view_i);
  void send_model_uniform(glm::mat4 model);
  void send_camera_pos_uniform(glm::vec3 pos);

  void send_diffuse_color_uniform(glm::vec3 color);
  void send_specular_color_uniform(glm::vec3 color_specular);
  void send_specular_color_power_uniform(float s);
  void send_diffuse_texutre_uniform(unsigned int texture_id);

  void send_bone_transform(glm::mat4 bone_transform,int i);


  void send_light_ambient(float a,int i);
  void send_light_pos(glm::vec3 pos,int i);
  void send_light_color(glm::vec3 color,int i);
  void send_light_sila(float sila,int i);
  void send_lights_pocet(unsigned int i);


  void send_spot_lights_ambient(float a,int i);
  void send_spot_lights_shadow_map(unsigned int texture_id, int i);
  void send_spot_light_pos(glm::vec3 pos,int i);
  void send_spot_light_color(glm::vec3 color,int i);
  void send_spot_light_sila(float sila,int i);
  void send_spot_lights_cut_off(float cut,int i);
  void send_spot_lights_dir(glm::vec3 dir, int i);
  void send_spot_lights_light_space_matrix(glm::mat4,int i);
  void send_spot_lights_pocet(unsigned int i);
  void send_spot_lights_bias(float b,int i);

  void send_global_light_dir(glm::vec3 dir);
  void send_global_light_color(glm::vec3 color);
  void send_global_light_status(bool status);
  void send_global_light_ambient(float a);


  void send_fog_type(int type);
  void send_fog_status(bool s);
  void send_fog_start(float v);
  void send_fog_end(float v);
  void send_fog_color(glm::vec3 color);
  void send_fog_density(float v);




  void send_global_light_space_matrix_uniform(glm::mat4 m);
  void send_global_depth_map(unsigned int mapa);

  void add_mesh(MESH_T*mesh);
  void clear_meshe();
  vector<MESH_T*> get_meshe();

  void register_uniforms();

private:
  void compile(string vertex_code,string framgnet_code);

  unsigned int projection_uniform;
  unsigned int view_uniform;
  unsigned int model_uniform;
  unsigned int camera_pos_uniform;
  unsigned int diffuse_color_uniform;
  unsigned int diffuse_texture_uniform;
  unsigned int specular_color_uniform;
  unsigned int specular_color_power_uniform;
  unsigned int shadow_map_uniform;

  unsigned int bones_transform_uniform[100];

  unsigned int lights_ambient_uniform[4];
  unsigned int lights_color_uniform[4];
  unsigned int lights_pos_uniform[4];
  unsigned int lights_sila_uniform[4];
  unsigned int lights_pocet_aktiv_uniform;

  unsigned int spot_lights_ambient_uniform[4];
  unsigned int spot_lights_shadow_map_uniform[4];
  unsigned int spot_lights_color_uniform[4];
  unsigned int spot_lights_pos_uniform[4];
  unsigned int spot_lights_sila_uniform[4];
  unsigned int spot_lights_dir_uniform[4];
  unsigned int spot_lights_cutoff_uniform[4];
  unsigned int spot_lights_light_space_matrix_uniform[4];
  unsigned int spot_lights_bias_uniform[4];
  unsigned int spot_lights_pocet_aktiv_uniform;

  unsigned int light_global_dir_uniform;
  unsigned int light_global_color_uniform;
  unsigned int light_global_status_uniform;
  unsigned int light_global_ambient_uniform;

  unsigned int light_space_matrix_uniform;
  unsigned int global_light_depth_map_uniform;


  unsigned int fog_type_uniform;
  unsigned int fog_status_uniform;
  unsigned int fog_color_uniform;
  unsigned int fog_start_uniform;
  unsigned int fog_end_uniform;
  unsigned int fog_density_uniform;

  vector<MESH_T*> meshe;
};


#endif
