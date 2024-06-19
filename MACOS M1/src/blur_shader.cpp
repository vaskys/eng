#include "blur_shader.h"
#include "shader.h"

BlurShader::BlurShader(string vertex_path,string fragment_path) : BaseShader(vertex_path,fragment_path) {
  register_uniforms();
}

BlurShader::~BlurShader(){
  BaseShader::~BaseShader();
}


void BlurShader::send_color_texture(unsigned int texture_id) {
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(color_texture_uniform,texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}


void BlurShader::send_dir(bool v) {
  glUniform1i(vertical_uniform_uniform,v);
}

void BlurShader::register_uniforms() {
  color_texture_uniform = glGetUniformLocation(id, "color_texture");
  vertical_uniform_uniform = glGetUniformLocation(id,"vertical");
}

void BlurShader::use() {
  glUseProgram(id);
}

