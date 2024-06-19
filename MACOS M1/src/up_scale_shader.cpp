#include "up_scale_shader.h"
#include "shader.h"

UpScaleShader::UpScaleShader(string vertex_path, string fragment_path) : BaseShader(vertex_path,fragment_path) {
  register_uniforms();
}

UpScaleShader::~UpScaleShader() {
  BaseShader::~BaseShader();
}


void UpScaleShader::use() {
  glUseProgram(id);
}

void UpScaleShader::send_color_texture(unsigned int texture_id) {
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(color_texture_uniform,texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}

void UpScaleShader::send_volumetric_texture(unsigned int texture_id) {
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(volumetric_texture_uniform,texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}


void UpScaleShader::register_uniforms() {
  color_texture_uniform = glGetUniformLocation(id,"color_texture");
  volumetric_texture_uniform = glGetUniformLocation(id,"volumetric_texture");
}
