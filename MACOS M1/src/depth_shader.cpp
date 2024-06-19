#include "depth_shader.h"
#include "SDL_opengl.h"
#include "config.h"

DepthShader::DepthShader(string vertex_path,string fragment_path ) : BaseShader(vertex_path,fragment_path) {
  register_uniforms();
}

DepthShader::~DepthShader() {
  BaseShader::~BaseShader();
}

void DepthShader::register_uniforms() {
  light_space_uniform = glGetUniformLocation(id,"light_space_matrix");
  model_uniform = glGetUniformLocation(id,"model");
}


void DepthShader::send_light_space_uniform(glm::mat4 light_space) {
  glUniformMatrix4fv(light_space_uniform, 1, GL_FALSE, glm::value_ptr(light_space));
}

void DepthShader::send_model_uniform(glm::mat4 model) {
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
}


void DepthShader::use() {
  glUseProgram(id);
}


///////////////////////////////////////////////////////////////////


PerspectiveDepthShader::PerspectiveDepthShader(string vertex_path,string fragment_path) : BaseShader(vertex_path,fragment_path) {
  register_uniforms();
}

PerspectiveDepthShader::~PerspectiveDepthShader() {
  BaseShader::~BaseShader();
}

void PerspectiveDepthShader::register_uniforms() {
  light_space_uniform = glGetUniformLocation(id,"light_space_matrix");
  model_uniform = glGetUniformLocation(id,"model");
  light_pos_uniform = glGetUniformLocation(id,"light_pos");
}

void PerspectiveDepthShader::use() {
  glUseProgram(id);
}

void PerspectiveDepthShader::send_light_space_uniform(glm::mat4 light_space) {
  glUniformMatrix4fv(light_space_uniform, 1, GL_FALSE, glm::value_ptr(light_space));
}

void PerspectiveDepthShader::send_model_uniform(glm::mat4 model) {
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
}

void PerspectiveDepthShader::send_light_pos_uniform(glm::vec3 pos) {
  glUniform3f(light_pos_uniform,pos.x,pos.y,pos.z);
}




DepthShaderAnimated::DepthShaderAnimated(string vertex_path,string fragment_path ) : BaseShader(vertex_path,fragment_path) {
  register_uniforms();
}

DepthShaderAnimated::~DepthShaderAnimated() {
  BaseShader::~BaseShader();
}

void DepthShaderAnimated::register_uniforms() {
  light_space_uniform = glGetUniformLocation(id,"light_space_matrix");
  model_uniform = glGetUniformLocation(id,"model");

  for(int i=0;i<100;i++)
  {
    string u_id="finalBonesMatrices["+to_string(i)+"]";
    bones_transform_uniform[i]=glGetUniformLocation(id,u_id.c_str());
  }
}


void DepthShaderAnimated::send_light_space_uniform(glm::mat4 light_space) {
  glUniformMatrix4fv(light_space_uniform, 1, GL_FALSE, glm::value_ptr(light_space));
}

void DepthShaderAnimated::send_model_uniform(glm::mat4 model) {
  glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
}


void DepthShaderAnimated::use() {
  glUseProgram(id);
}

void DepthShaderAnimated::send_bone_transform(glm::mat4 bone_transform,int id)
{
  glUniformMatrix4fv(bones_transform_uniform[id],1,GL_FALSE,glm::value_ptr(bone_transform));
}
