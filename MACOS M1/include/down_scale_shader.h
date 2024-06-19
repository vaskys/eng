#ifndef DOWN_SCALE_SHADER_H
#define DOWN_SCALE_SHADER_H

#include "shader.h"

class DownScaleShader : BaseShader {
public:
  DownScaleShader(string vertex_path,string fragment_path);
  ~DownScaleShader();

  void register_uniforms();
  void use();

  void send_depth_texture(unsigned int texture_id);
private:
  unsigned int depth_texture_uniform;
};

#endif

