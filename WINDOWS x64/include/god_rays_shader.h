#ifndef GOD_RAYS_SHADER_H
#define GOD_RAYS_SHADER_H

#include "config.h"
#include "shader.h"

class GodRaysShader : BaseShader {
public:
  GodRaysShader(string vertex_path,string fragment_path);
  ~GodRaysShader();

  void register_uniforms();
  void use();

  void send_decay_uniform(float v);
  void send_exposure_uniform(float v);
  void send_density_uniform(float v);
  void send_weight_uniform(float v);
  void send_ocluder_texture(unsigned int texture_id);
  void send_color_texture(unsigned int texture_id);
  void send_sun_pos_uniform(glm::vec2 pos);
private:
  unsigned int decay_uniform;
  unsigned int exposure_uniform;
  unsigned int density_uniform;
  unsigned int weight_uniform;

  unsigned int ocluder_texture;
  unsigned int color_texture;
  unsigned int sun_pos_uniform;

};

#endif
