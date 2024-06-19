#ifndef BLUR_SHADER_H
#define BLUR_SHADER_H

#include "shader.h"

class BlurShader : BaseShader {
public:
  BlurShader(string vertex_path, string fragment_path);
  ~BlurShader();

  void register_uniforms();
  void use();

  void send_color_texture(unsigned int texture_id);
  void send_dir(bool v);
private:
  unsigned int color_texture_uniform;
  unsigned int vertical_uniform_uniform;
};

#endif 
