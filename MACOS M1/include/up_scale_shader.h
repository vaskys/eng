#ifndef UP_SCALE_SHADER_H
#define UP_SCALE_SHADER_H


#include "shader.h"

class UpScaleShader : BaseShader {
public:
  UpScaleShader(string vertex_path,string fragment_path);
  ~UpScaleShader();

  void use();
  void register_uniforms();

  void send_color_texture(unsigned int color_texture);
  void send_volumetric_texture(unsigned int volumetric_texture);

private:
  unsigned int color_texture_uniform;
  unsigned int volumetric_texture_uniform;
};

#endif
