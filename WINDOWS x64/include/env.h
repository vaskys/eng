#ifndef ENV_H
#define ENV_H

#include "config.h"
#include "lights.h"

class Env
{
public:
  Env();
  ~Env();

  void add_light(LightNode *node);
  vector<LightNode*> get_lights();
  void remove_light(LightNode *node);
  void clear();

  glm::vec3 get_global_light_dir();
  glm::vec3 get_global_light_color();
  bool get_global_light_status();
  float get_global_light_ambient();

  void set_global_light_dir(glm::vec3 dir);
  void set_global_light_color(glm::vec3 color);
  void set_global_light_status(bool status);
  void set_global_light_ambient(float a);

  void set_global_light_default();


  void cal_global_light_matrix();
  glm::mat4 get_global_light_space_matrix();

  glm::mat4 get_global_light_view();
  glm::mat4 get_global_light_projection();


  float get_gr_decay();
  float get_gr_exposure();
  float get_gr_density();
  float get_gr_weight();

  void set_gr_decay(float v);
  void set_gr_exposure(float v);
  void set_gr_density(float v);
  void set_gr_weight(float v);


  void cal_gr_sun_pos();
  glm::vec2 get_gr_sun_pos();


  void set_gr_status(bool v);
  bool get_gr_status();

  glm::mat4 get_gr_decal_model();
  void cal_gr_decal_model();


  vector<SpotLightNode*> get_spot_lights();
  void add_spot_light(SpotLightNode *node);
  void remove_spot_light(SpotLightNode *node);

  bool redraw_shadow = true;


  void set_fog_type(int v);
  void set_fog_status(bool v);
  void set_fog_color(glm::vec3 color);
  void set_fog_start(float v);
  void set_fog_end(float v);
  void set_fog_density(float v);


  bool get_fog_status();
  glm::vec3 get_fog_color();
  float get_fog_start();
  float get_fog_end();
  float get_fog_density();
  int get_fog_type();

  float scatter_value;
  float volumetric_fog_density;

  void set_volumetric_light_status(bool i);
  bool get_volumetric_light_status();


  void set_volumetric_fog_status(int i);
  int get_volumetric_fog_status();

  glm::vec3 center;

private:
  vector<LightNode*> light_nodes;
  vector<SpotLightNode*> spot_light_nodes;


  glm::vec3 global_light_dir;
  glm::vec3 global_light_color;
  float global_light_ambient;
  bool global_light_status;


  glm::mat4 global_light_projection;
  glm::mat4 global_light_view;
  glm::mat4 global_light_space_matrix;


  float gr_decay;
  float gr_exposure;
  float gr_density;
  float gr_weight;

  glm::vec2 gr_sun_pos;

  bool gr_status;
  glm::mat4 gr_decal_model;


  int fog_type;
  bool fog_status;
  glm::vec3 fog_color;
  float fog_start;
  float fog_end;
  float fog_density;

  bool volumetric_light_status;
  int volumetric_fog_status;
};


#endif
