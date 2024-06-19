#ifndef DEPTH_SHADER_H
#define DEPTH_SHADER_H

#include "config.h"
#include "glm/fwd.hpp"
#include "shader.h"

class DepthShader : BaseShader {
public:
  DepthShader(string vertex_path,string fragment_path);
  ~DepthShader();

  void register_uniforms();

  void send_light_space_uniform(glm::mat4 light_space);
  void send_model_uniform(glm::mat4 model);

  void use();

private:
  unsigned int light_space_uniform;
  unsigned int model_uniform;

};

class PerspectiveDepthShader : BaseShader {
public:
  PerspectiveDepthShader(string vertex_path,string fragment_path);
  ~PerspectiveDepthShader();

  void register_uniforms();
  void send_light_space_uniform(glm::mat4 light_space);
  void send_model_uniform(glm::mat4 model);
  void send_light_pos_uniform(glm::vec3 pos);
  void use();
private:
  unsigned int light_space_uniform;
  unsigned int model_uniform;
  unsigned int light_pos_uniform;
};


class DepthShaderAnimated : BaseShader {
public:
  DepthShaderAnimated(string vertex_path,string fragment_path);
  ~DepthShaderAnimated();

  void register_uniforms();
  void send_light_space_uniform(glm::mat4 light_space);
  void send_model_uniform(glm::mat4 model);
  void send_bone_transform(glm::mat4 bone_transform,int i);

  void use();

private:
  unsigned int light_space_uniform;
  unsigned int model_uniform;

  unsigned int bones_transform_uniform[100];

};

#endif
