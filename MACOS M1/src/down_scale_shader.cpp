#include "down_scale_shader.h"
#include "shader.h"

DownScaleShader::DownScaleShader(string vertex_path, string fragment_path) : BaseShader(vertex_path,fragment_path) {
  register_uniforms();
}


DownScaleShader::~DownScaleShader() {
  BaseShader::~BaseShader();
}

void DownScaleShader::use() {
  glUseProgram(id);
}


void DownScaleShader::send_depth_texture(unsigned int texture_id) {
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(depth_texture_uniform,texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}

void DownScaleShader::register_uniforms() {
  depth_texture_uniform = glGetUniformLocation(id, "depth_texture");
}
