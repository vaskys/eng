#ifndef OC_GR_SHADER_H
#define OC_GR_SHADER_H

#include "config.h"
#include "shader.h"

class OcGRShader : BaseShader {
public:
  OcGRShader(string vertex_path, string fragment_path);
  ~OcGRShader();

  void register_uniforms();
  void use();

  void send_color_uniform(glm::vec3 color);
  void send_projection_uniform(glm::mat4 projection);
  void send_view_uniform(glm::mat4 view);
  void send_model_uniform(glm::mat4 model);
private:
  unsigned int color_uniform;
  unsigned int projection_uniform;
  unsigned int view_uniform;
  unsigned int model_uniform;

};


class OcGRShaderAnimated : BaseShader {
public:
  OcGRShaderAnimated(string vertex_path, string fragment_path);
  ~OcGRShaderAnimated();

  void register_uniforms();
  void use();

  void send_color_uniform(glm::vec3 color);
  void send_projection_uniform(glm::mat4 projection);
  void send_view_uniform(glm::mat4 view);
  void send_model_uniform(glm::mat4 model);

  void send_bone_transform(glm::mat4 bone_transform,int i);
private:
  unsigned int color_uniform;
  unsigned int projection_uniform;
  unsigned int view_uniform;
  unsigned int model_uniform;

  unsigned int bones_transform_uniform[100];

};

#endif
