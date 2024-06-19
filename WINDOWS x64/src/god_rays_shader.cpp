#include "god_rays_shader.h"
#include "shader.h"

GodRaysShader::GodRaysShader(string vertex_path,string fragment_path) : BaseShader(vertex_path,fragment_path) {
  register_uniforms();
}


GodRaysShader::~GodRaysShader() {
  BaseShader::~BaseShader();
}


void GodRaysShader::use() {
  glUseProgram(id);
}

void GodRaysShader::register_uniforms() {
  decay_uniform = glGetUniformLocation(id,"decay");
  exposure_uniform = glGetUniformLocation(id,"exposure");
  density_uniform = glGetUniformLocation(id,"density");
  weight_uniform = glGetUniformLocation(id,"weight");
  ocluder_texture = glGetUniformLocation(id,"ocluder_texture");
  color_texture = glGetUniformLocation(id,"color_texture");

  sun_pos_uniform = glGetUniformLocation(id,"sun_pos");

}

void GodRaysShader::send_color_texture(unsigned texture_id) {
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(color_texture,texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}


void GodRaysShader::send_ocluder_texture(unsigned texture_id) {
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(ocluder_texture,texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}

void GodRaysShader::send_decay_uniform(float v) {
  glUniform1f(decay_uniform,v);
}

void GodRaysShader::send_exposure_uniform(float v) {
  glUniform1f(exposure_uniform,v);
}

void GodRaysShader::send_density_uniform(float v) {
  glUniform1f(density_uniform,v);
}

void GodRaysShader::send_weight_uniform(float v) {
  glUniform1f(weight_uniform,v);
}


void GodRaysShader::send_sun_pos_uniform(glm::vec2 pos) {
  glUniform2f(sun_pos_uniform,pos.x,pos.y);
}

